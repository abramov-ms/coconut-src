# Содержание

1. Переключение контекста (сисколлы, preemption тредов).
1. NPTL. task_struct. PID vs TGID vs TID.
1. Многопоточная синхронизация. Примеры data race и race condition.
1. Зачем нужны атомики, как они реализованы.
1. Thread sanitizer, типичные виды ошибок.
1. Спинлок, cache coherency. Мьютекс, futex.
1. Condvar, очереди сообщений и thread pool.
1. Lock freedom, lock-free stack.

# Ссылки

1. https://en.wikipedia.org/wiki/Protection_ring
1. https://utcc.utoronto.ca/~cks/space/blog/linux/PidsTgidsAndTasks
1. https://www.scss.tcd.ie/Jeremy.Jones/VivioJS/caches/MESIHelp.htm
1. https://en.cppreference.com/w/c/thread
1. https://en.wikipedia.org/wiki/Non-blocking_algorithm
