# lab1 实验报告

## 练习一
****

### **题目**

理解通过make生成执行文件的过程。（要求在报告中写出对下述问题的回答）

列出本实验各练习中对应的OS原理的知识点，并说明本实验中的实现部分如何对应和体现了原理中的基本概念和关键知识点。

在此练习中，大家需要通过静态分析代码来了解：

      操作系统镜像文件ucore.img是如何一步一步生成的？(需要比较详细地解释Makefile中每一条相关命令和命令参数的含义，以及说明命令导致的结果)

      一个被系统认为是符合规范的硬盘主引导扇区的特征是什么？

### **解答**

**操作系统镜像文件ucore.img是如何一步一步生成的？(需要比较详细地解释Makefile中每一条相关命令和命令参数的含义，以及说明命令导致的结果)**

#### 通过make V= 生成的make 生成过程

    附带注释，只是目前为止本人的理解，不保证正确性。


~~~
cd lab1  # 进入lab1文件夹中
make clean  # 清除之前生成的项目
make V=  # 获取make 的生成过程
~~~

**生成过程如下**

~~~
+ cc kern/init/init.c   # 编译Ucore系统内核启动文件 init.c
gcc -Ikern/init/ -march=i686 -fno-builtin -fno-PIC -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/init/init.c -o obj/kern/init/init.o
kern/init/init.c:95:1: warning: ‘lab1_switch_test’ defined but not used [-Wunused-function]
   95 | lab1_switch_test(void) {
      | ^~~~~~~~~~~~~~~~
+ cc kern/libs/stdio.c  # 编译标准输入输出库 
gcc -Ikern/libs/ -march=i686 -fno-builtin -fno-PIC -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/libs/stdio.c -o obj/kern/libs/stdio.o
+ cc kern/libs/readline.c # 一个用于(从stdin中)读取一行内容的方法
gcc -Ikern/libs/ -march=i686 -fno-builtin -fno-PIC -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/libs/readline.c -o obj/kern/libs/readline.o
+ cc kern/debug/panic.c   # 一个用于发出报错的方法（不确定，现阶段的理解）
gcc -Ikern/debug/ -march=i686 -fno-builtin -fno-PIC -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/debug/panic.c -o obj/kern/debug/panic.o
kern/debug/panic.c: In function ‘__panic’:
kern/debug/panic.c:27:5: warning: implicit declaration of function ‘print_stackframe’; did you mean ‘print_trapframe’? [-Wimplicit-function-declaration]
   27 |     print_stackframe();
      |     ^~~~~~~~~~~~~~~~
      |     print_trapframe
+ cc kern/debug/kdebug.c # 包含几个debug 方法，打印信息，二分查找地址等
gcc -Ikern/debug/ -march=i686 -fno-builtin -fno-PIC -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/debug/kdebug.c -o obj/kern/debug/kdebug.o
kern/debug/kdebug.c:251:1: warning: ‘read_eip’ defined but not used [-Wunused-function]
  251 | read_eip(void) {
      | ^~~~~~~~
+ cc kern/debug/kmonitor.c # 简单的命令行内核监视器
gcc -Ikern/debug/ -march=i686 -fno-builtin -fno-PIC -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/debug/kmonitor.c -o obj/kern/debug/kmonitor.o
+ cc kern/driver/clock.c  # 好像是时钟中断信号 
gcc -Ikern/driver/ -march=i686 -fno-builtin -fno-PIC -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/driver/clock.c -o obj/kern/driver/clock.o
+ cc kern/driver/console.c # 初始化显示器，连续内存（不确定）
gcc -Ikern/driver/ -march=i686 -fno-builtin -fno-PIC -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/driver/console.c -o obj/kern/driver/console.o
+ cc kern/driver/picirq.c # 初始化程序中断控制器 pic (不确定)
gcc -Ikern/driver/ -march=i686 -fno-builtin -fno-PIC -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/driver/picirq.c -o obj/kern/driver/picirq.o
+ cc kern/driver/intr.c # irq 的 enable 和disable
gcc -Ikern/driver/ -march=i686 -fno-builtin -fno-PIC -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/driver/intr.c -o obj/kern/driver/intr.o
+ cc kern/trap/trap.c # 暂未深入研究
gcc -Ikern/trap/ -march=i686 -fno-builtin -fno-PIC -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/trap/trap.c -o obj/kern/trap/trap.o
kern/trap/trap.c: In function ‘print_trapframe’:
kern/trap/trap.c:100:16: warning: taking address of packed member of ‘struct trapframe’ may result in an unaligned pointer value [-Waddress-of-packed-member]
  100 |     print_regs(&tf->tf_regs);
      |                ^~~~~~~~~~~~
At top level:
kern/trap/trap.c:30:26: warning: ‘idt_pd’ defined but not used [-Wunused-variable]
   30 | static struct pseudodesc idt_pd = {
      |                          ^~~~~~
kern/trap/trap.c:14:13: warning: ‘print_ticks’ defined but not used [-Wunused-function]
   14 | static void print_ticks() {
      |             ^~~~~~~~~~~
+ cc kern/trap/vectors.S # 一段汇编代码，还未研究是干吗的
gcc -Ikern/trap/ -march=i686 -fno-builtin -fno-PIC -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/trap/vectors.S -o obj/kern/trap/vectors.o
+ cc kern/trap/trapentry.S # 一段汇编代码，还未研究是干吗的
gcc -Ikern/trap/ -march=i686 -fno-builtin -fno-PIC -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/trap/trapentry.S -o obj/kern/trap/trapentry.o
+ cc kern/mm/pmm.c  # 好像根中断描述符有关
gcc -Ikern/mm/ -march=i686 -fno-builtin -fno-PIC -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/mm/pmm.c -o obj/kern/mm/pmm.o
+ cc libs/string.c # String 字符串依赖
gcc -Ilibs/ -march=i686 -fno-builtin -fno-PIC -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/  -c libs/string.c -o obj/libs/string.o
+ cc libs/printfmt.c # 好像是格式化输出依赖
gcc -Ilibs/ -march=i686 -fno-builtin -fno-PIC -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/  -c libs/printfmt.c -o obj/libs/printfmt.o
+ ld bin/kernel  #将上面编译的文件转化为可执行文件，即系统内核存储在 bin/kernel中
ld -m    elf_i386 -nostdlib -T tools/kernel.ld -o bin/kernel  obj/kern/init/init.o obj/kern/libs/stdio.o obj/kern/libs/readline.o obj/kern/debug/panic.o obj/kern/debug/kdebug.o obj/kern/debug/kmonitor.o obj/kern/driver/clock.o obj/kern/driver/console.o obj/kern/driver/picirq.o obj/kern/driver/intr.o obj/kern/trap/trap.o obj/kern/trap/vectors.o obj/kern/trap/trapentry.o obj/kern/mm/pmm.o  obj/libs/string.o obj/libs/printfmt.o
+ cc boot/bootasm.S  # 编译bootasm.S文件，这个是当前lab中 Bootloader的一部分，其主要目的是被cpu调用，然后该文件调用bootmain.c文件， 同时该文件还将系统设置成了保护模式，以及一个栈用于c语言代码的调用
gcc -Iboot/ -march=i686 -fno-builtin -fno-PIC -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Os -nostdinc -c boot/bootasm.S -o obj/boot/bootasm.o
+ cc boot/bootmain.c # 编译bootmain.c文件
gcc -Iboot/ -march=i686 -fno-builtin -fno-PIC -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Os -nostdinc -c boot/bootmain.c -o obj/boot/bootmain.o
+ cc tools/sign.c  # 编译sign.c文件 该文件好像是用于获取符合规范的磁盘主引导扇区的内容，及将磁盘主引导扇区的内容加载到内存中，同时还有校验主引导扇区中的内容是否符合要求（不确定）
gcc -Itools/ -g -Wall -O2 -c tools/sign.c -o obj/sign/tools/sign.o
gcc -g -Wall -O2 obj/sign/tools/sign.o -o bin/sign
+ ld bin/bootblock  # 将上面生成的*.o文件通过ld命令链接成bin 目录下的bootblock文件
ld -m    elf_i386 -nostdlib -N -e start -Ttext 0x7C00 obj/boot/bootasm.o obj/boot/bootmain.o -o obj/bootblock.o
'obj/bootblock.out' size: 496 bytes
build 512 bytes boot sector: 'bin/bootblock' success!
dd if=/dev/zero of=bin/ucore.img count=10000  # /dev/zero 作为输入文件的作用是将无数个0写入文件（这边是10000个）
记录了10000+0 的读入
记录了10000+0 的写出
5120000字节（5.1 MB，4.9 MiB）已复制，0.0313203 s，163 MB/s
dd if=bin/bootblock of=bin/ucore.img conv=notrunc 
记录了1+0 的读入
记录了1+0 的写出
512字节已复制，0.000126482 s，4.0 MB/s
dd if=bin/kernel of=bin/ucore.img seek=1 conv=notrunc
记录了154+1 的读入
记录了154+1 的写出
78916字节（79 kB，77 KiB）已复制，0.000435106 s，181 MB/s  # 以上两个dd 命令将之前生成的 bootblock 和 kernel写入到ucore.img中 这时这个虚拟磁盘镜像就生成了
~~~


**/dev/zero文件的描述**

     /dev/zero 是类 Unix 系统中一个特殊的文件，当读取该文件时，它会提供无限的空字符 null。它的一个主要用途是提供字符流来初始化数据存储，也就是使用空字符覆盖目标数据。另一个常见的用法是产生一个特定大小的空白文件。

      你可以从 /dev/zero 读取任意大小数量的 null 字符。和 /dev/null 不同，/dev/zero 不但可以作为数据黑洞，也可以作为数据源泉。你可以将数据写入 /dev/zero 文件，但实际上不会有任何影响。不过一般我们还是使用 /dev/null 来做这件事。


**总结ucore.img操作系统镜像生成的过程**

下面内容有借鉴其他人的答案（如 ： https://blog.csdn.net/qq_41946412/article/details/103091369）
   1. 通过gcc编译器，将kernel文件夹下的.c文件编译成Obj目录下的.o文件

   2. 通过ld命令以及提供给我们的kernel.ld脚本文件将.o文件 链接为bin目录下的kernel可执行文件，且该文件是一个ELF格式的 32位可执行文件 具体如下所示
   ~~~
leezed@leezed-Ubuntu:~/projects/ucore/os_kernel_lab/labcodes/lab1/bin$ file kernel 

kernel: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), statically linked, not stripped

   #该文件可以说是ucore系统内核文件（目前我的理解）
   ~~~

   3. 然后将boot目录下的.c.S文件 以及tools下的sign.c文件编译成.o文件

   4.  通过ld命令将刚刚生成的文件链接成bin/bootblock文件，该文件是一个目前lab1的bootloader 如下所示

   ~~~
   leezed@leezed-Ubuntu:~/projects/ucore/os_kernel_lab/labcodes/lab1/bin$ file bootblock 

   bootblock: DOS/MBR boot sector
   ~~~

   5. 通过dd命令将上方生成的bootblock 和 kernel 生成操作系统镜像ucore.img


**一个被系统认为是符合规范的硬盘主引导扇区的特征是什么？**

      这部分我其实没有研究出来，查了别人的博客才发现说是bootloader的验证(特征)是在sign.c中的

      原文链接  https://blog.csdn.net/qq_41946412/article/details/103091369

   ~~~
    char buf[512];
    memset(buf, 0, sizeof(buf));
    FILE *ifp = fopen(argv[1], "rb");
    int size = fread(buf, 1, st.st_size, ifp);
    if (size != st.st_size) {
        fprintf(stderr, "read '%s' error, size is %d.\n", argv[1], size);
        return -1;
    }
    fclose(ifp);
    buf[510] = 0x55;
    buf[511] = 0xAA;
    FILE *ofp = fopen(argv[2], "wb+");
    size = fwrite(buf, 1, 512, ofp);
    if (size != 512) {
        fprintf(stderr, "write '%s' error, size is %d.\n", argv[2], size);
        return -1;
    }
    fclose(ofp);
    printf("build 512 bytes boot sector: '%s' success!\n", argv[2]);
    return 0;
   ~~~

符合规范的硬盘主引导扇区的特征应该包括，

①大小为512个字节，

②没用到的其他位置设置为0，

③第511个字节0x55，第512个字节是0xAA，也就是说，最后一个和倒数第二个字节的内容是确定的，

④如果读出的字节数不是512，需要报错。

即应该可以读出512.


## 练习二 

****

###  **题目**

使用qemu执行并调试lab1中的软件。（要求在报告中简要写出练习过程）
为了熟悉使用qemu和gdb进行的调试工作，我们进行如下的小练习：

1. 从CPU加电后执行的第一条指令开始，单步跟踪BIOS的执行。
2. 在初始化位置0x7c00设置实地址断点,测试断点正常。
3. 从0x7c00开始跟踪代码运行,将单步跟踪反汇编得到的代码与bootasm.S和 bootblock.asm进行比较。
4. 自己找一个bootloader或内核中的代码位置，设置断点并进行测试。

### **解答**


~~~
 $ cd labcodes_answer/lab1_result/
 $ make lab1-mon 在命令行中输入该命令即可进入调试模式
~~~

查看makefile文件中该命令的所在地

~~~
lab1-mon: $(UCOREIMG)
        $(V)$(TERMINAL) -e "$(QEMU) -S -s -d in_asm -D $(BINDIR)/q.log -monitor stdio -hda $< -serial null"
        $(V)sleep 2
        $(V)$(TERMINAL) -e "gdb -q -x tools/lab1init"
~~~

通过上面的代码我们可以看出来，这个代码大致是干了两件事

1. 是把qemu 执行的指令记录下来放在 q.log中
2. 和我们的gdb结合来调试我们的bootloader,调试指令放在tools/lab1init中，下面我们来看一下这些指令

~~~
# 这些都是gdb可以识别的命令
file bin/kernel  # 这条命令是在加载bin/kernel
target remote :1234 # 与qemu进行连接
set architecture i8086 # 设置cpu结构为 i8086 (我的理解)
b *0x7c00 # 这个是设置断点 # 设置bootloader启动的断点
continue # 然后让系统继续运行
x /2i $pc # 打印相应的指令  i是指令的意思 /2i 的意思即是打印两条指令
~~~

通过课程的知识我们可以知道，当cpu加电启动bios后，等到bios进入0x7c00处，开始运行bootloader的代码，把控制权交给bootloader

在命令行输入make lab1-mon后，弹出来几个窗口，其中有qemu窗口以及gdb调试窗口

其中qdb调试窗口显示如下
~~~
0x0000fff0 in ?? ()
The target architecture is assumed to be i8086
Breakpoint 1 at 0x7c00

Breakpoint 1, 0x00007c00 in ?? ()
=> 0x7c00:	cli    
   0x7c01:	cld    
(gdb)    
~~~

输入 x /10i $pc 指令，我们就可以打印出pc指令寄存器之后的10条指令

如下
~~~
(gdb) x /10i $pc
=> 0x7c00:	cli    
   0x7c01:	cld    
   0x7c02:	xor    %eax,%eax
   0x7c04:	mov    %eax,%ds
   0x7c06:	mov    %eax,%es
   0x7c08:	mov    %eax,%ss
   0x7c0a:	in     $0x64,%al
   0x7c0c:	test   $0x2,%al
   0x7c0e:	jne    0x7c0a
   0x7c10:	mov    $0xd1,%al
~~~

而这些指令正好与我们boot/bootasm.S文件中第16行开始是对应的
bootasm.S文件中的代码如下
~~~
# start address should be 0:7c00, in real mode, the beginning address of the running bootloader
.globl start
start:
.code16                                             # Assemble for 16-bit mode
    cli                                             # Disable interrupts
    cld                                             # String operations increment

    # Set up the important data segment registers (DS, ES, SS).
    xorw %ax, %ax                                   # Segment number zero
    movw %ax, %ds                                   # -> Data Segment
    movw %ax, %es                                   # -> Extra Segment
    movw %ax, %ss                                   # -> Stack Segment

    # Enable A20:
    #  For backwards compatibility with the earliest PCs, physical
    #  address line 20 is tied low, so that addresses higher than
    #  1MB wrap around to zero by default. This code undoes this.
~~~


**接下来我们从cpu加电的第一条指令来跟踪**

ps:[如果你的cgdb调试时出现了\[34m 等颜色代码，可以看这篇文章](https://blog.csdn.net/Leezed525/article/details/124728458?spm=1001.2014.3001.5502)

回想上课说的cpu加点第一条指令是在cs:ip的位置，即cs寄存器的值左移四位加上eip 寄存器的值

首先使用make clean ，再make debug进行跟踪调试

随即我们就可以打开cgdb调试页面

![123](../../images/2022-05-13_21-54.png)












