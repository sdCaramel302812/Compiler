.class public compiler_hw3
.super java/lang/Object
.method public static foo(II)I
.limit stack 50
.limit locals 50
	iload 0
	ldc 6
	iadd
	istore 0
	iload 0
	ireturn
.end method
.method public static lol(I)V
.limit stack 50
.limit locals 50
	iload 0
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	return
.end method
.method public static main([Ljava/lang/String;)V
.limit stack 50
.limit locals 50
	ldc 0
	istore 0
	iload 0
	ldc 4
	invokstatic compiler_hw3/foo(II)I
	istore 0
	iload 0
	invokstatic compiler_hw3/lol(I)V
	return
.end method
