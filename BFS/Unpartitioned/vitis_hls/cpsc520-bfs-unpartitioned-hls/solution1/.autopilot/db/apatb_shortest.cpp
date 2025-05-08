#include <systemc>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdint.h>
#include "SysCFileHandler.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include <complex>
#include <stdbool.h>
#include "autopilot_cbe.h"
#include "hls_stream.h"
#include "hls_half.h"
#include "hls_signal_handler.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

// wrapc file define:
#define AUTOTB_TVIN_column_indices "../tv/cdatafile/c.shortest.autotvin_column_indices.dat"
#define AUTOTB_TVOUT_column_indices "../tv/cdatafile/c.shortest.autotvout_column_indices.dat"
#define AUTOTB_TVIN_row_offsets "../tv/cdatafile/c.shortest.autotvin_row_offsets.dat"
#define AUTOTB_TVOUT_row_offsets "../tv/cdatafile/c.shortest.autotvout_row_offsets.dat"
#define AUTOTB_TVIN_visited "../tv/cdatafile/c.shortest.autotvin_visited.dat"
#define AUTOTB_TVOUT_visited "../tv/cdatafile/c.shortest.autotvout_visited.dat"
#define AUTOTB_TVIN_queue "../tv/cdatafile/c.shortest.autotvin_queue.dat"
#define AUTOTB_TVOUT_queue "../tv/cdatafile/c.shortest.autotvout_queue.dat"
#define AUTOTB_TVIN_src "../tv/cdatafile/c.shortest.autotvin_src.dat"
#define AUTOTB_TVOUT_src "../tv/cdatafile/c.shortest.autotvout_src.dat"
#define AUTOTB_TVIN_input_r "../tv/cdatafile/c.shortest.autotvin_input_r.dat"
#define AUTOTB_TVOUT_input_r "../tv/cdatafile/c.shortest.autotvout_input_r.dat"
#define AUTOTB_TVIN_output_r "../tv/cdatafile/c.shortest.autotvin_output_r.dat"
#define AUTOTB_TVOUT_output_r "../tv/cdatafile/c.shortest.autotvout_output_r.dat"

#define INTER_TCL "../tv/cdatafile/ref.tcl"

// tvout file define:
#define AUTOTB_TVOUT_PC_column_indices "../tv/rtldatafile/rtl.shortest.autotvout_column_indices.dat"
#define AUTOTB_TVOUT_PC_row_offsets "../tv/rtldatafile/rtl.shortest.autotvout_row_offsets.dat"
#define AUTOTB_TVOUT_PC_visited "../tv/rtldatafile/rtl.shortest.autotvout_visited.dat"
#define AUTOTB_TVOUT_PC_queue "../tv/rtldatafile/rtl.shortest.autotvout_queue.dat"
#define AUTOTB_TVOUT_PC_src "../tv/rtldatafile/rtl.shortest.autotvout_src.dat"
#define AUTOTB_TVOUT_PC_input_r "../tv/rtldatafile/rtl.shortest.autotvout_input_r.dat"
#define AUTOTB_TVOUT_PC_output_r "../tv/rtldatafile/rtl.shortest.autotvout_output_r.dat"


static const bool little_endian()
{
  int a = 1;
  return *(char*)&a == 1;
}

inline static void rev_endian(char* p, size_t nbytes)
{
  std::reverse(p, p+nbytes);
}

template<size_t bit_width>
struct transaction {
  typedef uint64_t depth_t;
  static const size_t wbytes = (bit_width+7)>>3;
  static const size_t dbytes = sizeof(depth_t);
  const depth_t depth;
  const size_t vbytes;
  const size_t tbytes;
  char * const p;
  typedef char (*p_dat)[wbytes];
  p_dat vp;

  transaction(depth_t depth)
    : depth(depth), vbytes(wbytes*depth), tbytes(dbytes+vbytes),
      p(new char[tbytes]) {
    *(depth_t*)p = depth;
    rev_endian(p, dbytes);
    vp = (p_dat) (p+dbytes);
  }

  void reorder() {
    rev_endian(p, dbytes);
    p_dat vp = (p_dat) (p+dbytes);
    for (depth_t i = 0; i < depth; ++i) {
      rev_endian(vp[i], wbytes);
    }
  }

  template<size_t psize>
  void import(char* param, depth_t num, int64_t offset) {
    param -= offset*psize;
    for (depth_t i = 0; i < num; ++i) {
      memcpy(vp[i], param, wbytes);
      param += psize;
      if (little_endian()) {
        rev_endian(vp[i], wbytes);
      }
    }
    vp += num;
  }

  template<size_t psize>
  void send(char* param, depth_t num) {
    for (depth_t i = 0; i < num; ++i) {
      memcpy(param, vp[i], wbytes);
      param += psize;
    }
    vp += num;
  }

  template<size_t psize>
  void send(char* param, depth_t num, int64_t skip) {
    for (depth_t i = 0; i < num; ++i) {
      memcpy(param, vp[skip+i], wbytes);
      param += psize;
    }
  }

  ~transaction() { if (p) { delete[] p; } }
};


inline static const std::string begin_str(int num)
{
  return std::string("[[transaction]]           ")
         .append(std::to_string(num))
         .append("\n");
}

inline static const std::string end_str()
{
  return std::string("[[/transaction]]\n");
}

const std::string formatData(unsigned char *pos, size_t wbits)
{
  bool LE = little_endian();
  size_t wbytes = (wbits+7)>>3;
  size_t i = LE ? wbytes-1 : 0;
  auto next = [&] () {
    auto c = pos[i];
    LE ? --i : ++i;
    return c;
  };
  std::ostringstream ss;
  ss << "0x";
  if (int t = (wbits & 0x7)) {
    if (t <= 4) {
      unsigned char mask = (1<<t)-1;
      ss << std::hex << std::setfill('0') << std::setw(1)
         << (int) (next() & mask);
      wbytes -= 1;
    }
  }
  for (size_t i = 0; i < wbytes; ++i) {
    ss << std::hex << std::setfill('0') << std::setw(2) << (int)next();
  }
  ss.put('\n');
  return ss.str();
}

static bool RTLOutputCheckAndReplacement(std::string &data)
{
  bool changed = false;
  for (size_t i = 2; i < data.size(); ++i) {
    if (data[i] == 'X' || data[i] == 'x') {
      data[i] = '0';
      changed = true;
    }
  }
  return changed;
}

struct SimException : public std::exception {
  const char *msg;
  const size_t line;
  SimException(const char *msg, const size_t line)
    : msg(msg), line(line)
  {
  }
};

template<size_t bit_width>
class PostCheck
{
  static const char *bad;
  static const char *err;
  std::fstream stream;
  std::string s;

  void send(char *p, ap_uint<bit_width> &data, size_t l, size_t rest)
  {
    if (rest == 0) {
      if (!little_endian()) {
        const size_t wbytes = (bit_width+7)>>3;
        rev_endian(p-wbytes, wbytes);
      }
    } else if (rest < 8) {
      *p = data.range(l+rest-1, l).to_uint();
      send(p+1, data, l+rest, 0);
    } else {
      *p = data.range(l+8-1, l).to_uint();
      send(p+1, data, l+8, rest-8);
    }
  }

  void readline()
  {
    std::getline(stream, s);
    if (stream.eof()) {
      throw SimException(bad, __LINE__);
    }
  }

public:
  char *param;
  size_t psize;
  size_t depth;

  PostCheck(const char *file)
  {
    stream.open(file);
    if (stream.fail()) {
      throw SimException(err, __LINE__);
    } else {
      readline();
      if (s != "[[[runtime]]]") {
        throw SimException(bad, __LINE__);
      }
    }
  }

  ~PostCheck() noexcept(false)
  {
    stream.close();
  }

  void run(size_t AESL_transaction_pc, size_t skip)
  {
    if (stream.peek() == '[') {
      readline();
    }

    for (size_t i = 0; i < skip; ++i) {
      readline();
    }

    bool foundX = false;
    for (size_t i = 0; i < depth; ++i) {
      readline();
      foundX |= RTLOutputCheckAndReplacement(s);
      ap_uint<bit_width> data(s.c_str(), 16);
      send(param+i*psize, data, 0, bit_width);
    }
    if (foundX) {
      std::cerr << "WARNING: [SIM 212-201] RTL produces unknown value "
                << "'x' or 'X' on some port, possible cause: "
                << "There are uninitialized variables in the design.\n";
    }

    if (stream.peek() == '[') {
      readline();
    }
  }
};

template<size_t bit_width>
const char* PostCheck<bit_width>::bad = "Bad TV file";

template<size_t bit_width>
const char* PostCheck<bit_width>::err = "Error on TV file";
      
class INTER_TCL_FILE {
  public:
INTER_TCL_FILE(const char* name) {
  mName = name; 
  column_indices_depth = 0;
  row_offsets_depth = 0;
  visited_depth = 0;
  queue_depth = 0;
  src_depth = 0;
  input_r_depth = 0;
  output_r_depth = 0;
  trans_num =0;
}
~INTER_TCL_FILE() {
  mFile.open(mName);
  if (!mFile.good()) {
    cout << "Failed to open file ref.tcl" << endl;
    exit (1); 
  }
  string total_list = get_depth_list();
  mFile << "set depth_list {\n";
  mFile << total_list;
  mFile << "}\n";
  mFile << "set trans_num "<<trans_num<<endl;
  mFile.close();
}
string get_depth_list () {
  stringstream total_list;
  total_list << "{column_indices " << column_indices_depth << "}\n";
  total_list << "{row_offsets " << row_offsets_depth << "}\n";
  total_list << "{visited " << visited_depth << "}\n";
  total_list << "{queue " << queue_depth << "}\n";
  total_list << "{src " << src_depth << "}\n";
  total_list << "{input_r " << input_r_depth << "}\n";
  total_list << "{output_r " << output_r_depth << "}\n";
  return total_list.str();
}
void set_num (int num , int* class_num) {
  (*class_num) = (*class_num) > num ? (*class_num) : num;
}
void set_string(std::string list, std::string* class_list) {
  (*class_list) = list;
}
  public:
    int column_indices_depth;
    int row_offsets_depth;
    int visited_depth;
    int queue_depth;
    int src_depth;
    int input_r_depth;
    int output_r_depth;
    int trans_num;
  private:
    ofstream mFile;
    const char* mName;
};


extern "C" void shortest_hw_stub_wrapper(volatile void *, volatile void *, volatile void *, volatile void *, int);

extern "C" void apatb_shortest_hw(volatile void * __xlx_apatb_param_column_indices, volatile void * __xlx_apatb_param_row_offsets, volatile void * __xlx_apatb_param_visited, volatile void * __xlx_apatb_param_queue, int __xlx_apatb_param_src) {
  refine_signal_handler();
  fstream wrapc_switch_file_token;
  wrapc_switch_file_token.open(".hls_cosim_wrapc_switch.log");
static AESL_FILE_HANDLER aesl_fh;
  int AESL_i;
  if (wrapc_switch_file_token.good())
  {

    CodeState = ENTER_WRAPC_PC;
    static unsigned AESL_transaction_pc = 0;
    string AESL_token;
    string AESL_num;
#ifdef USE_BINARY_TV_FILE
{
transaction<32> tr(9442);
aesl_fh.read(AUTOTB_TVOUT_PC_output_r, tr.p, tr.tbytes);
if (little_endian()) { tr.reorder(); }
tr.send<4>((char*)__xlx_apatb_param_visited, 4721, 0);
tr.send<4>((char*)__xlx_apatb_param_queue, 4721, 4721);
}
#else
try {
static PostCheck<32> pc(AUTOTB_TVOUT_PC_output_r);
pc.psize = 4;
pc.param = (char*)__xlx_apatb_param_visited;
pc.depth = 4721;
pc.run(AESL_transaction_pc, 0);pc.param = (char*)__xlx_apatb_param_queue;
pc.depth = 4721;
pc.run(AESL_transaction_pc, 0);

} catch (SimException &e) {
  std::cout << "at line " << e.line << " occurred exception, " << e.msg << "\n";
}
#endif

    AESL_transaction_pc++;
    return ;
  }
static unsigned AESL_transaction;
static INTER_TCL_FILE tcl_file(INTER_TCL);
std::vector<char> __xlx_sprintf_buffer(1024);
CodeState = ENTER_WRAPC;
CodeState = DUMP_INPUTS;
unsigned __xlx_offset_byte_param_column_indices = 0;
unsigned __xlx_offset_byte_param_row_offsets = 0;
unsigned __xlx_offset_byte_param_visited = 0;
unsigned __xlx_offset_byte_param_queue = 0;
#ifdef USE_BINARY_TV_FILE
{
aesl_fh.touch(AUTOTB_TVIN_input_r, 'b');
transaction<32> tr(32166);
__xlx_offset_byte_param_column_indices = 0*4;
if (__xlx_apatb_param_column_indices) {
  tr.import<4>((char*)__xlx_apatb_param_column_indices, 27444, 0);
}
__xlx_offset_byte_param_row_offsets = 27444*4;
if (__xlx_apatb_param_row_offsets) {
  tr.import<4>((char*)__xlx_apatb_param_row_offsets, 4722, 0);
}
aesl_fh.write(AUTOTB_TVIN_input_r, tr.p, tr.tbytes);
tcl_file.set_num(32166, &tcl_file.input_r_depth);
}
#else
aesl_fh.touch(AUTOTB_TVIN_input_r);
{
aesl_fh.write(AUTOTB_TVIN_input_r, begin_str(AESL_transaction));
__xlx_offset_byte_param_column_indices = 0*4;
if (__xlx_apatb_param_column_indices) {
for (size_t i = 0; i < 27444; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_column_indices + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_input_r, s);
}
}
__xlx_offset_byte_param_row_offsets = 27444*4;
if (__xlx_apatb_param_row_offsets) {
for (size_t i = 0; i < 4722; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_row_offsets + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_input_r, s);
}
}
tcl_file.set_num(32166, &tcl_file.input_r_depth);
aesl_fh.write(AUTOTB_TVIN_input_r, end_str());
}
#endif
#ifdef USE_BINARY_TV_FILE
{
aesl_fh.touch(AUTOTB_TVIN_output_r, 'b');
transaction<32> tr(9442);
__xlx_offset_byte_param_visited = 0*4;
if (__xlx_apatb_param_visited) {
  tr.import<4>((char*)__xlx_apatb_param_visited, 4721, 0);
}
__xlx_offset_byte_param_queue = 4721*4;
if (__xlx_apatb_param_queue) {
  tr.import<4>((char*)__xlx_apatb_param_queue, 4721, 0);
}
aesl_fh.write(AUTOTB_TVIN_output_r, tr.p, tr.tbytes);
tcl_file.set_num(9442, &tcl_file.output_r_depth);
}
#else
aesl_fh.touch(AUTOTB_TVIN_output_r);
{
aesl_fh.write(AUTOTB_TVIN_output_r, begin_str(AESL_transaction));
__xlx_offset_byte_param_visited = 0*4;
if (__xlx_apatb_param_visited) {
for (size_t i = 0; i < 4721; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_visited + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_output_r, s);
}
}
__xlx_offset_byte_param_queue = 4721*4;
if (__xlx_apatb_param_queue) {
for (size_t i = 0; i < 4721; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_queue + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVIN_output_r, s);
}
}
tcl_file.set_num(9442, &tcl_file.output_r_depth);
aesl_fh.write(AUTOTB_TVIN_output_r, end_str());
}
#endif
// print column_indices Transactions
{
aesl_fh.write(AUTOTB_TVIN_column_indices, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_column_indices;
aesl_fh.write(AUTOTB_TVIN_column_indices, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.column_indices_depth);
aesl_fh.write(AUTOTB_TVIN_column_indices, end_str());
}

// print row_offsets Transactions
{
aesl_fh.write(AUTOTB_TVIN_row_offsets, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_row_offsets;
aesl_fh.write(AUTOTB_TVIN_row_offsets, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.row_offsets_depth);
aesl_fh.write(AUTOTB_TVIN_row_offsets, end_str());
}

// print visited Transactions
{
aesl_fh.write(AUTOTB_TVIN_visited, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_visited;
aesl_fh.write(AUTOTB_TVIN_visited, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.visited_depth);
aesl_fh.write(AUTOTB_TVIN_visited, end_str());
}

// print queue Transactions
{
aesl_fh.write(AUTOTB_TVIN_queue, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_offset_byte_param_queue;
aesl_fh.write(AUTOTB_TVIN_queue, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.queue_depth);
aesl_fh.write(AUTOTB_TVIN_queue, end_str());
}

// print src Transactions
{
aesl_fh.write(AUTOTB_TVIN_src, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_src;
aesl_fh.write(AUTOTB_TVIN_src, formatData(pos, 32));
}
  tcl_file.set_num(1, &tcl_file.src_depth);
aesl_fh.write(AUTOTB_TVIN_src, end_str());
}

CodeState = CALL_C_DUT;
shortest_hw_stub_wrapper(__xlx_apatb_param_column_indices, __xlx_apatb_param_row_offsets, __xlx_apatb_param_visited, __xlx_apatb_param_queue, __xlx_apatb_param_src);
CodeState = DUMP_OUTPUTS;
#ifdef USE_BINARY_TV_FILE
{
aesl_fh.touch(AUTOTB_TVOUT_output_r, 'b');
transaction<32> tr(9442);
__xlx_offset_byte_param_visited = 0*4;
if (__xlx_apatb_param_visited) {
  tr.import<4>((char*)__xlx_apatb_param_visited, 4721, 0);
}
__xlx_offset_byte_param_queue = 4721*4;
if (__xlx_apatb_param_queue) {
  tr.import<4>((char*)__xlx_apatb_param_queue, 4721, 0);
}
aesl_fh.write(AUTOTB_TVOUT_output_r, tr.p, tr.tbytes);
tcl_file.set_num(9442, &tcl_file.output_r_depth);
}
#else
aesl_fh.touch(AUTOTB_TVOUT_output_r);
{
aesl_fh.write(AUTOTB_TVOUT_output_r, begin_str(AESL_transaction));
__xlx_offset_byte_param_visited = 0*4;
if (__xlx_apatb_param_visited) {
for (size_t i = 0; i < 4721; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_visited + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_output_r, s);
}
}
__xlx_offset_byte_param_queue = 4721*4;
if (__xlx_apatb_param_queue) {
for (size_t i = 0; i < 4721; ++i) {
unsigned char *pos = (unsigned char*)__xlx_apatb_param_queue + i * 4;
std::string s = formatData(pos, 32);
aesl_fh.write(AUTOTB_TVOUT_output_r, s);
}
}
tcl_file.set_num(9442, &tcl_file.output_r_depth);
aesl_fh.write(AUTOTB_TVOUT_output_r, end_str());
}
#endif
CodeState = DELETE_CHAR_BUFFERS;
AESL_transaction++;
tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
}
