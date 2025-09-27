#include <errno.h>
#include <string.h>

#define FUSE_USE_VERSION 30
#include <fuse3/fuse.h>

void* trollfs_init(struct fuse_conn_info* conn, struct fuse_config* cfg) {
  (void)conn;

  // Use our custom st_ino-s.
  cfg->use_ino = 1;

  return NULL;
}

void trollfs_destroy(void* private_data) {
  // No-op.
  (void)private_data;
}

int trollfs_getattr(const char* path, struct stat* st,
                    struct fuse_file_info* fi) {
  (void)fi;

  if (strcmp(path, "/") == 0) {
    st->st_nlink = 2;
    st->st_mode = S_IFDIR | 0444;
    st->st_ino = 42;
    return 0;
  } else if (strcmp(path, "/the_only_file") == 0) {
    st->st_nlink = 1;
    st->st_mode = S_IFREG | 0444;
    st->st_ino = 61;
    return 0;
  } else {
    return -ENOENT;
  }
}

int trollfs_readdir(const char* path, void* buf, fuse_fill_dir_t filler,
                    off_t off, struct fuse_file_info* fi,
                    enum fuse_readdir_flags flags) {
  (void)off;
  (void)fi;
  (void)flags;

  if (strcmp(path, "/") != 0) {
    return -ENOENT;
  }

  filler(buf, ".", NULL, 0, 0);
  filler(buf, "..", NULL, 0, 0);
  filler(buf, "the_only_file", NULL, 0, 0);

  return 0;
}

int main(int argc, char* argv[]) {
  struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
  fuse_opt_parse(&args, /*data=*/NULL, /*opts=*/NULL, /*proc=*/NULL);

  struct fuse_operations ops = {
      .init = trollfs_init,
      .destroy = trollfs_destroy,
      .readdir = trollfs_readdir,
      .getattr = trollfs_getattr,
  };

  return fuse_main(args.argc, args.argv, &ops, NULL);
}
