

#define SIMPLEFS_MAGIC 0x10032013
#define SIMPLEFS_JOURNAL_MAGIC = 0x20032013

#define SIMPLEFS_DEFAULT_BLOCK_SIZE 4096
#define SIMPLEFS_FILENAME_MAXLEN 255
#define SIMPLEFS_START_INO 10
/**
 * Резервирование узлов для супер-блока, хранилища узлов
 * и информационного блока
 */
#define SIMPLEFS_RESERVED_INODES 3

#ifdef SIMPLEFS_DEBUG
#define sfs_trace(fmt, ...) {                       \
	printk(KERN_ERR "[simplefs] %s +%d:" fmt,       \
	       __FILE__, __LINE__, ##__VA_ARGS__);      \
}
#define sfs_debug(level, fmt, ...) {                \
	printk(level "[simplefs]:" fmt, ##__VA_ARGS__); \
}
#else
#define sfs_trace(fmt, ...) no_printk(fmt, ##__VA_ARGS__)
#define sfs_debug(level, fmt, ...) no_printk(fmt, ##__VA_ARGS__)
#endif

/*Номер узла для корневой директории */
const int SIMPLEFS_ROOTDIR_INODE_NUMBER = 1;

/*блок на диске,где сохраняется супер-блок */
const int SIMPLEFS_SUPERBLOCK_BLOCK_NUMBER = 0;

/*блок на диске, где сохраняются узлы*/
const int SIMPLEFS_INODESTORE_BLOCK_NUMBER = 1;

/*настройки*/
const int SIMPLEFS_JOURNAL_INODE_NUMBER = 2;
const int SIMPLEFS_JOURNAL_BLOCK_NUMBER = 2;
const int SIMPLEFS_JOURNAL_BLOCKS = 2;

/*Блок диска, где сохраняются  пары "имя + номер узла" корневой директории*/
const int SIMPLEFS_ROOTDIR_DATABLOCK_NUMBER = 4;

#define SIMPLEFS_LAST_RESERVED_BLOCK SIMPLEFS_ROOTDIR_DATABLOCK_NUMBER
#define SIMPLEFS_LAST_RESERVED_INODE SIMPLEFS_JOURNAL_INODE_NUMBER

/* Пара "имя + номер узла" для каждого файла в директории.
 * Хранятся в качестве информации директории */
struct simplefs_dir_record {
	char filename[SIMPLEFS_FILENAME_MAXLEN];
	uint64_t inode_no;
};

struct simplefs_inode {
	mode_t mode;
	uint64_t inode_no;
	uint64_t data_block_number;

	union {
		uint64_t file_size;
		uint64_t dir_children_count;
	};
};
const int SIMPLEFS_MAX_FILESYSTEM_OBJECTS_SUPPORTED = 64;
struct journal_s;
struct simplefs_super_block {
	uint64_t version;
	uint64_t magic;
	uint64_t block_size;

	uint64_t inodes_count;

	uint64_t free_blocks;

	struct journal_s *journal;

	char padding[4048];
};
