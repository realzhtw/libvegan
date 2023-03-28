#include <vegan/platform/fs.h>
#include <vegan/c_string.h>
#include <vegan/vector_ref.h>
#include <vegan/bsearch.h>

#include <sys/types.h>
#include <dirent.h>

namespace {
  using namespace vegan;
  using namespace vegan::platform;
  using fs::file_type;

  const int _file_type_map[] = {
    DT_UNKNOWN, (int)file_type::unknown,
    DT_FIFO,    (int)file_type::fifo,
    DT_CHR,     (int)file_type::character_device,
    DT_DIR,     (int)file_type::directory,
    DT_BLK,     (int)file_type::block_device,
    DT_REG,     (int)file_type::regular,
    DT_LNK,     (int)file_type::link,
    DT_SOCK,    (int)file_type::socket
  };
  const_vector_ref<int> file_type_map{_file_type_map};

  file_type translate_file_type(int platform_file_type)
  {
    auto fts = slice(file_type_map, 0, 2);
    Long pos = bsearch(fts, platform_file_type);
    return pos < fts.size() ? file_type{*(fts.ptr(pos) + 1)} : file_type::unknown;
  }

}

namespace vegan {
  namespace platform {

    dir *opendir(const char *name) { return (dir *)::opendir(name); }
    void closedir(dir *d) { ::closedir((DIR *)d); }

    

    bool readdir(dir *d, direntry *e)
    {
      dirent *pl_ent = ::readdir((DIR *)d);
      if (pl_ent == nullptr) return false;
      e->name = string_ref{pl_ent->d_name, pl_ent->d_namlen};
      e->type = translate_file_type(pl_ent->d_type);
      return true;
    }

  }
}
