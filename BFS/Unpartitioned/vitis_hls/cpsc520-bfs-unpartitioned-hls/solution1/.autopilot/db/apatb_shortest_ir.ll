; ModuleID = '/home/wuyue/yangliu/cpsc520-final-project/BFS/Unpartitioned/vitis_hls/cpsc520-bfs-unpartitioned-hls/solution1/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

; Function Attrs: noinline
define void @apatb_shortest_ir(i32* noalias nocapture nonnull readonly %column_indices, i32* noalias nocapture nonnull readonly %row_offsets, i32* noalias nocapture nonnull %visited, i32* noalias nocapture nonnull %queue, i32 %src) local_unnamed_addr #0 {
entry:
  %malloccall = tail call i8* @malloc(i64 109776)
  %column_indices_copy = bitcast i8* %malloccall to [27444 x i32]*
  %malloccall1 = tail call i8* @malloc(i64 18888)
  %row_offsets_copy = bitcast i8* %malloccall1 to [4722 x i32]*
  %malloccall2 = tail call i8* @malloc(i64 18884)
  %visited_copy = bitcast i8* %malloccall2 to [4721 x i32]*
  %malloccall3 = tail call i8* @malloc(i64 18884)
  %queue_copy = bitcast i8* %malloccall3 to [4721 x i32]*
  %0 = bitcast i32* %column_indices to [27444 x i32]*
  %1 = bitcast i32* %row_offsets to [4722 x i32]*
  %2 = bitcast i32* %visited to [4721 x i32]*
  %3 = bitcast i32* %queue to [4721 x i32]*
  call fastcc void @copy_in([27444 x i32]* nonnull %0, [27444 x i32]* %column_indices_copy, [4722 x i32]* nonnull %1, [4722 x i32]* %row_offsets_copy, [4721 x i32]* nonnull %2, [4721 x i32]* %visited_copy, [4721 x i32]* nonnull %3, [4721 x i32]* %queue_copy)
  %4 = getelementptr inbounds [27444 x i32], [27444 x i32]* %column_indices_copy, i32 0, i32 0
  %5 = getelementptr inbounds [4722 x i32], [4722 x i32]* %row_offsets_copy, i32 0, i32 0
  %6 = getelementptr inbounds [4721 x i32], [4721 x i32]* %visited_copy, i32 0, i32 0
  %7 = getelementptr inbounds [4721 x i32], [4721 x i32]* %queue_copy, i32 0, i32 0
  call void @apatb_shortest_hw(i32* %4, i32* %5, i32* %6, i32* %7, i32 %src)
  call void @copy_back([27444 x i32]* %0, [27444 x i32]* %column_indices_copy, [4722 x i32]* %1, [4722 x i32]* %row_offsets_copy, [4721 x i32]* %2, [4721 x i32]* %visited_copy, [4721 x i32]* %3, [4721 x i32]* %queue_copy)
  tail call void @free(i8* %malloccall)
  tail call void @free(i8* %malloccall1)
  tail call void @free(i8* %malloccall2)
  tail call void @free(i8* %malloccall3)
  ret void
}

declare noalias i8* @malloc(i64) local_unnamed_addr

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_in([27444 x i32]* noalias readonly, [27444 x i32]* noalias, [4722 x i32]* noalias readonly, [4722 x i32]* noalias, [4721 x i32]* noalias readonly, [4721 x i32]* noalias, [4721 x i32]* noalias readonly, [4721 x i32]* noalias) unnamed_addr #1 {
entry:
  call fastcc void @onebyonecpy_hls.p0a27444i32([27444 x i32]* %1, [27444 x i32]* %0)
  call fastcc void @onebyonecpy_hls.p0a4722i32([4722 x i32]* %3, [4722 x i32]* %2)
  call fastcc void @onebyonecpy_hls.p0a4721i32([4721 x i32]* %5, [4721 x i32]* %4)
  call fastcc void @onebyonecpy_hls.p0a4721i32([4721 x i32]* %7, [4721 x i32]* %6)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a27444i32([27444 x i32]* noalias, [27444 x i32]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [27444 x i32]* %0, null
  %3 = icmp eq [27444 x i32]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [27444 x i32], [27444 x i32]* %0, i64 0, i64 %for.loop.idx1
  %src.addr = getelementptr [27444 x i32], [27444 x i32]* %1, i64 0, i64 %for.loop.idx1
  %5 = load i32, i32* %src.addr, align 4
  store i32 %5, i32* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 27444
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a4722i32([4722 x i32]* noalias, [4722 x i32]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [4722 x i32]* %0, null
  %3 = icmp eq [4722 x i32]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [4722 x i32], [4722 x i32]* %0, i64 0, i64 %for.loop.idx1
  %src.addr = getelementptr [4722 x i32], [4722 x i32]* %1, i64 0, i64 %for.loop.idx1
  %5 = load i32, i32* %src.addr, align 4
  store i32 %5, i32* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 4722
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a4721i32([4721 x i32]* noalias, [4721 x i32]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [4721 x i32]* %0, null
  %3 = icmp eq [4721 x i32]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [4721 x i32], [4721 x i32]* %0, i64 0, i64 %for.loop.idx1
  %src.addr = getelementptr [4721 x i32], [4721 x i32]* %1, i64 0, i64 %for.loop.idx1
  %5 = load i32, i32* %src.addr, align 4
  store i32 %5, i32* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 4721
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_out([27444 x i32]* noalias, [27444 x i32]* noalias readonly, [4722 x i32]* noalias, [4722 x i32]* noalias readonly, [4721 x i32]* noalias, [4721 x i32]* noalias readonly, [4721 x i32]* noalias, [4721 x i32]* noalias readonly) unnamed_addr #3 {
entry:
  call fastcc void @onebyonecpy_hls.p0a27444i32([27444 x i32]* %0, [27444 x i32]* %1)
  call fastcc void @onebyonecpy_hls.p0a4722i32([4722 x i32]* %2, [4722 x i32]* %3)
  call fastcc void @onebyonecpy_hls.p0a4721i32([4721 x i32]* %4, [4721 x i32]* %5)
  call fastcc void @onebyonecpy_hls.p0a4721i32([4721 x i32]* %6, [4721 x i32]* %7)
  ret void
}

declare void @free(i8*) local_unnamed_addr

declare void @apatb_shortest_hw(i32*, i32*, i32*, i32*, i32)

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_back([27444 x i32]* noalias, [27444 x i32]* noalias readonly, [4722 x i32]* noalias, [4722 x i32]* noalias readonly, [4721 x i32]* noalias, [4721 x i32]* noalias readonly, [4721 x i32]* noalias, [4721 x i32]* noalias readonly) unnamed_addr #3 {
entry:
  call fastcc void @onebyonecpy_hls.p0a4721i32([4721 x i32]* %4, [4721 x i32]* %5)
  call fastcc void @onebyonecpy_hls.p0a4721i32([4721 x i32]* %6, [4721 x i32]* %7)
  ret void
}

define void @shortest_hw_stub_wrapper(i32*, i32*, i32*, i32*, i32) #4 {
entry:
  %5 = bitcast i32* %0 to [27444 x i32]*
  %6 = bitcast i32* %1 to [4722 x i32]*
  %7 = bitcast i32* %2 to [4721 x i32]*
  %8 = bitcast i32* %3 to [4721 x i32]*
  call void @copy_out([27444 x i32]* null, [27444 x i32]* %5, [4722 x i32]* null, [4722 x i32]* %6, [4721 x i32]* null, [4721 x i32]* %7, [4721 x i32]* null, [4721 x i32]* %8)
  %9 = bitcast [27444 x i32]* %5 to i32*
  %10 = bitcast [4722 x i32]* %6 to i32*
  %11 = bitcast [4721 x i32]* %7 to i32*
  %12 = bitcast [4721 x i32]* %8 to i32*
  call void @shortest_hw_stub(i32* %9, i32* %10, i32* %11, i32* %12, i32 %4)
  call void @copy_in([27444 x i32]* null, [27444 x i32]* %5, [4722 x i32]* null, [4722 x i32]* %6, [4721 x i32]* null, [4721 x i32]* %7, [4721 x i32]* null, [4721 x i32]* %8)
  ret void
}

declare void @shortest_hw_stub(i32*, i32*, i32*, i32*, i32)

attributes #0 = { noinline "fpga.wrapper.func"="wrapper" }
attributes #1 = { argmemonly noinline norecurse "fpga.wrapper.func"="copyin" }
attributes #2 = { argmemonly noinline norecurse "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #3 = { argmemonly noinline norecurse "fpga.wrapper.func"="copyout" }
attributes #4 = { "fpga.wrapper.func"="stub" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}
