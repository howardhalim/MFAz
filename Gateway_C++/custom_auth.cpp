#define FUSE_USE_VERSION 31
#include <fuse.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include <cstring>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

#include "gateway_auto.h" // Include your custom header for auth functions

using namespace std;

static int initial_mount = 0;

// Function to split a string by a delimiter and return a vector of strings
vector<string> splitString(const string &str, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

// Define a root path (assuming you will set this to your desired mount point)
const char* root_path = "~/Desktop/test/custom_auth_fs";

// FUSE access function
static int custom_auth_access(const char *path, int mask)
{
    if(!initial_mount){
        printf("Initial Mount");
        initial_mount = 1;
        return 0;
    }
    //read parameters
    FILE *params = fopen("custom_authorization.txt","r");
    char param3[300];
    fgets(param3, 300, params);
    size_t len = strlen(param3);
    if(len>0 && param3[len-1] == '\n'){
        param3[len-1] = '\0';
    }
    int param4;
    fscanf(params, "%d", &param4);
    fclose(params);

    cout<<param3<<endl<<param4<<endl;

    // Simulate extraction of arguments
    string list1Str = "read,write"; 
    string list2Str = "resc1,resc2"; 
    char *choice = param3;
    int timer_choice  = param4; 

    // Split the lists into vectors of strings
    vector<string> Oi = splitString(list1Str, ',');
    vector<string> Ri = splitString(list2Str, ',');

    char res[300];

    // Custom authorization logic
    if(choice[0] == '0')
    {
        snprintf(res, sizeof(res), "%s", authUserRequest(Oi, Ri));
    }
    else
    {
        char* SGAi = choice;
        switch (timer_choice)
        {
            case 1:
                snprintf(res, sizeof(res), "%s", userTimerRequest(Oi, Ri, SGAi));
                break;
            case 2:
                snprintf(res, sizeof(res), "%s", userTimerGenerationRequest(Oi, Ri, SGAi));
                break;
            case 3:
                snprintf(res, sizeof(res), "%s", userTimerStoringRequest(Oi, Ri, SGAi));
                break;
            case 4:
                snprintf(res, sizeof(res), "%s", userTimerVerificationRequest(Oi, Ri, SGAi));
                break;
            default:
                snprintf(res, sizeof(res), "%s", userRequest(Oi, Ri, SGAi));
        }
    }

    // Check if authentication was successful
    if (strcmp(res, "Access Denied") == 0)
    {
        fprintf(stderr, "Access denied by custom authorization.\n");
        return -EACCES; // Access denied
    }

    // // get current Timestamp in UNIX format
    time_t t = time(NULL);
    char Ts[20];
    snprintf(Ts, sizeof(Ts), "%ld", t);

    uid_t userid = getuid();
    int Ui = static_cast<int>(userid);
    char user[30];
    sprintf(user,"%d",Ui);

    char filename[500];
    sprintf(filename, "granted_access/%s/granted_access_%s",user, Ts); //manually change the granted access save file number
    FILE *file = fopen(filename, "w");
    // Write the content of the res array to the file
    fprintf(file, "%s", res);

    // Close the file
    fclose(file);
    cout << "Access Granted!\n";
    return 0; // Access granted
}

static int custom_auth_getattr(const char *path, struct stat *stbuf)
{
    int res = 0;
    char full_path[1024];

    memset(stbuf, '\0', sizeof(struct stat));

    stbuf->st_mode = S_IFDIR | 0755;
    stbuf->st_nlink = 1;
    stbuf->st_size = 2048;
    stbuf->st_uid = getuid();
    stbuf->st_gid = getgid();
    stbuf->st_atime = stbuf->st_mtime = time(NULL);

    // snprintf(full_path, sizeof(full_path), "%s%s", root_path, path);

    // res = lstat(full_path, stbuf);
    // if (res == -1)
    //     return -errno;

    return res;
}

static void *custom_fuse_init(struct fuse_conn_info *conn){
    (void) conn;
    printf("-->my_fuse_init() has been invoked;\n");
    // initial_mount = 0;
    return NULL;
}

static int custom_auth_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                               off_t offset, struct fuse_file_info *fi)
{
    DIR *dp;
    struct dirent *de;
    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s%s", root_path, path);

    dp = opendir(full_path);
    if (dp == NULL)
        return -errno;

    while ((de = readdir(dp)) != NULL)
    {
        struct stat st;
        memset(&st, 0, sizeof(st));
        st.st_ino = de->d_ino;
        st.st_mode = de->d_type << 12;
        if (filler(buf, de->d_name, &st, 0))
            break;
    }

    closedir(dp);
    return 0;
}

static int custom_auth_open(const char *path, struct fuse_file_info *fi)
{
    int res;
    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s%s", root_path, path);

    res = open(full_path, fi->flags);
    if (res == -1)
        return -errno;

    close(res);
    return 0;
}

static int custom_auth_read(const char *path, char *buf, size_t size, off_t offset,
                            struct fuse_file_info *fi)
{
    int fd;
    int res;
    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s%s", root_path, path);

    fd = open(full_path, O_RDONLY);
    if (fd == -1)
        return -errno;

    res = pread(fd, buf, size, offset);
    if (res == -1)
        res = -errno;

    close(fd);
    return res;
}

static struct fuse_operations custom_auth_oper = {
    .getattr = custom_auth_getattr,
    .readdir = custom_auth_readdir,
    .init = custom_fuse_init,
    // .open = custom_auth_open,
    // .read = custom_auth_read,
    .access = custom_auth_access,
};

int main(int argc, char *argv[])
{
    return fuse_main(argc, argv, &custom_auth_oper, NULL);
}
