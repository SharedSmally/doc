
## [ELF](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format)

Each ELF file is made up of one ELF header, followed by file data. The data can include:
- Program header table, describing zero or more memory segments
- Section header table, describing zero or more sections
- Data referred to by entries in the program header table or section header table

A program header table, if present, tells the system how to create a process image. Files used to build a process
image (execute a program) must have a program header table; relocatable files do not need one. A
section header table contains information describing the file’s sections. Every section has an entry in the
table; each entry gives information such as the section name, the section size, etc. Files used during linking
must have a section header table; other object files may or may not have one.

```
$hexdump -n 64 -C  test
00000000  7f 45 4c 46 02 01 01 00  00 00 00 00 00 00 00 00  |.ELF............|
00000010  02 00 3e 00 01 00 00 00  e0 2a 48 00 00 00 00 00  |..>......*H.....|
00000020  40 00 00 00 00 00 00 00  88 54 b1 00 00 00 00 00  |@........T......|
00000030  00 00 00 00 40 00 38 00  09 00 40 00 25 00 22 00  |....@.8...@.%.".|
00000040

$ readelf -h  test
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x482ae0
  Start of program headers:          64 (bytes into file)
  Start of section headers:          11621512 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         9
  Size of section headers:           64 (bytes)
  Number of section headers:         37
  Section header string table index: 34

$readelf -l test
Elf file type is EXEC (Executable file)
Entry point 0x482ae0
There are 9 program headers, starting at offset 64

Program Headers:
  Type           Offset             VirtAddr           PhysAddr
                 FileSiz            MemSiz              Flags  Align
  PHDR           0x0000000000000040 0x0000000000400040 0x0000000000400040
                 0x00000000000001f8 0x00000000000001f8  R E    8
  INTERP         0x0000000000000238 0x0000000000400238 0x0000000000400238
                 0x000000000000001c 0x000000000000001c  R      1
      [Requesting program interpreter: /lib64/ld-linux-x86-64.so.2]
  LOAD           0x0000000000000000 0x0000000000400000 0x0000000000400000
                 0x000000000018a6f9 0x000000000018a6f9  R E    200000
  LOAD           0x000000000018af60 0x000000000078af60 0x000000000078af60
                 0x0000000000005810 0x0000000000006790  RW     200000
  DYNAMIC        0x000000000018eab0 0x000000000078eab0 0x000000000078eab0
                 0x0000000000000420 0x0000000000000420  RW     8
  NOTE           0x0000000000000254 0x0000000000400254 0x0000000000400254
                 0x0000000000000020 0x0000000000000020  R      4
  GNU_EH_FRAME   0x000000000015a584 0x000000000055a584 0x000000000055a584
                 0x0000000000007a0c 0x0000000000007a0c  R      4
  GNU_STACK      0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000000 0x0000000000000000  RW     10
  GNU_RELRO      0x000000000018af60 0x000000000078af60 0x000000000078af60
                 0x00000000000040a0 0x00000000000040a0  R      1

 Section to Segment mapping:
  Segment Sections...
   00
   01     .interp
   02     .interp .note.ABI-tag .hash .dynsym .dynstr .gnu.version .gnu.version_r 
          .rela.dyn .rela.plt .init .plt .text .fini .rodata .eh_frame_hdr
          .eh_frame .gcc_except_table
   03     .init_array .fini_array .jcr .data.rel.ro .dynamic .got .got.plt .data .bss
   04     .dynamic
   05     .note.ABI-tag
   06     .eh_frame_hdr
   07
   08     .init_array .fini_array .jcr .data.rel.ro .dynamic .got

$$readelf -S  test
There are 37 section headers, starting at offset 0xb15488:
Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .interp           PROGBITS         0000000000400238  00000238
       000000000000001c  0000000000000000   A       0     0     1
...
  [36] .strtab           STRTAB           0000000000000000  00ac72c8
       000000000004e1ba  0000000000000000           0     0     1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), l (large)
  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)
  O (extra OS processing required) o (OS specific), p (processor specific)
```
