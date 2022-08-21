#include "dfs_file.h"

#define DFS_FNODE_HASH_NR 128

struct dfs_fnode_mgr
{
    struct rt_mutex lock;
    rt_list_t head[DFS_FNODE_HASH_NR];
};

static struct dfs_fnode_mgr dfs_fm;

void dfs_fnode_mgr_init(void)
{
    int i = 0;

    rt_mutex_init(&dfs_fm.lock, "dfs_mgr", RT_IPC_FLAG_PRIO);
    for (i = 0; i < DFS_FNODE_HASH_NR; i++)
    {
        rt_list_init(&dfs_fm.head[i]);
    }
}