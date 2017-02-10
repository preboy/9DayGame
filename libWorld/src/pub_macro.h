#pragma  once
//#ifdef _DEBUG
//#define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
//#endif

// 安全删除指针;
#define SAFE_FREE( p )              \
if( p != NULL )                     \
{                                   \
    free(p);                        \
    p = NULL;                       \
}

#define SAFE_DELETE( p )            \
    if ( p != NULL )                \
    {                               \
    delete p;                       \
    p = NULL;                       \
    }

#define SAFE_DELETE_ARR( p )        \
    if ( p != NULL )                \
    {                               \
    delete[] p;                     \
    p = NULL;                       \
    }    

#define SAFE_RELEASE( p )           \
    if( p != NULL )                 \
    {                               \
        p->Release();               \
        p = NULL;                   \
    }

#define SAFE_RELEASE_AND_DEL( p )   \
    if( p != NULL )                 \
    {                               \
        p->Release();               \
        delete p;                   \
        p = NULL;                   \
    }

#define  CREATE_INS( CLASS )        \
    public:                         \
    static CLASS*    GetInstance()  \
    {                               \
    static CLASS i;                 \
    return &i;                      \
    };

#define ZERO_STRUCT( T )            \
    T()                             \
    {                               \
    memset( this, 0x0, sizeof(T));  \
    }
        
// 如果FALSE则返回;
#define FALSE_RETURN(b)             \
if(!b) return false;

#define NULL_RETURN(b) if(!b) return false;
