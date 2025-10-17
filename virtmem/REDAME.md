# Содержание

1. Виртуальные адреса.
1. `/proc/pid/maps`, layout виртуального адресного пространства.
1. `mmap()`, сортировка во внешней памяти.
1. Выделение памяти через `malloc()`. `mmap()` vs. `brk()`.
1. Кеши, профилирование с помощью valgrind.
1. Симуляция работы конвейера через `llvm-mca`.

# Ссылки

1. [Маппинг виртуальных страниц в физические](https://sergey-v-galtsev.gitlab.io/labs-description/lab/book/2-mm-6-address-space-2-translate.svg)
1. [Trie](https://en.wikipedia.org/wiki/Trie)
1. [x86_64::structures::paging::PageTableFlags](https://sergey-v-galtsev.gitlab.io/labs-description/doc/x86_64/structures/paging/page_table/struct.PageTableFlags.html)
1. [On vsyscall and vDSO](https://lwn.net/Articles/446528/)
1. [TLB cache](https://en.wikipedia.org/wiki/Translation_lookaside_buffer)
1. [Table of x86 Registers](https://en.wikipedia.org/wiki/X86#/media/File:Table_of_x86_Registers_svg.svg)
1. [Virtual address space](https://en.wikipedia.org/wiki/Virtual_address_space#/media/File:Virtual_address_space_and_physical_address_space_relationship.svg)
