# Содержание

1. Виртуальные адреса.
1. `mmap()`, сортировка во внешней памяти.
1. `/proc/pid/maps`, layout виртуального адресного пространства.
1. Выделение памяти через `malloc()`. `mmap()` vs. `brk()`.
1. Кеши, профилирование с помощью valgrind.
1. Симуляция работы конвейера через `llvm-mca`.

# Ссылки

1. [Маппинг виртуальных страниц в
   физические](https://sergey-v-galtsev.gitlab.io/labs-description/lab/book/2-mm-6-address-space-2-translate.svg)
1. [Trie](https://en.wikipedia.org/wiki/Trie)
1. [x86_64::structures::paging::PageTableFlags](https://sergey-v-galtsev.gitlab.io/labs-description/doc/x86_64/structures/paging/page_table/struct.PageTableFlags.html)
1. [TLB cache](https://en.wikipedia.org/wiki/Translation_lookaside_buffer)
