#include "traverse.h"

std::string CurrentPath() {

    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    return std::string(cwd);
}

std::string GetPath(const char* path) {

    std::string pwd;


    if(chdir(path) == -1){
        return pwd;
    }

    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));


    return std::string(cwd);
}

std::vector<std::string> DirectoryFullSearch(const char *path) {

    char cwd[PATH_MAX];
    strncpy(cwd, path, strlen(path));

    struct dirent **namelist;
    int count;
    int idx;

    std::vector<std::string> path_list;

    if ((count = scandir(path, &namelist, NULL, alphasort)) == -1) {
        return path_list;
    }

    for (idx = 0; idx < count; idx++) {
        path_list.push_back(namelist[idx]->d_name);
    }

    for (idx = 0; idx < count; idx++) {
        free(namelist[idx]);
    }

    free(namelist);

    return path_list;
}

std::unordered_map<std::string, std::string> FileInfo(const char *path) {

    std::unordered_map<std::string, std::string> info_map;

    Stat attr;
    if(stat(path, &attr) == -1){
        return info_map;
    }

    // print UID with passwd
    struct passwd *pwd;
    pwd = getpwuid(attr.st_uid);
    info_map["uid"] = pwd->pw_name;

    // print GID with group
    struct group *grp;
    grp = getgrgid(attr.st_gid);
    info_map["gid"] = grp->gr_name;

    // print size
    info_map["size"] = std::to_string(attr.st_size);

    // print path type // directory or file //S_ISREG – file // S_ISDIR – directory // Boolean (1 or 0)
    if(S_ISREG(attr.st_mode)){
        info_map["type"] = "file";

    }
    else if(S_ISDIR(attr.st_mode)){
        info_map["type"] = "directory";
    }

    // print permission
    char *perm = check_perm(attr);
    info_map["perm"] = perm;

    // print atime / ctime / mtime with ctime in string
    std::string aTime = std::string(ctime(&attr.st_atime));
    aTime.erase(aTime.find_first_of("\n"));
    info_map["atime"] = aTime;
    std::string mTime = std::string(ctime(&attr.st_mtime));
    mTime.erase(mTime.find_first_of("\n"));
    info_map["mtime"] = mTime;
    std::string cTime = std::string(ctime(&attr.st_ctime));
    cTime.erase(cTime.find_first_of("\n"));
    info_map["ctime"] = cTime;


    return info_map;
}

char *check_perm(Stat attr) {
    char *modeval = (char *) malloc(sizeof(char) * 9 + 1);

    mode_t perm = attr.st_mode;
    modeval[0] = (perm & S_IRUSR) ? 'r' : '-';
    modeval[1] = (perm & S_IWUSR) ? 'w' : '-';
    modeval[2] = (perm & S_IXUSR) ? 'x' : '-';
    modeval[3] = (perm & S_IRGRP) ? 'r' : '-';
    modeval[4] = (perm & S_IWGRP) ? 'w' : '-';
    modeval[5] = (perm & S_IXGRP) ? 'x' : '-';
    modeval[6] = (perm & S_IROTH) ? 'r' : '-';
    modeval[7] = (perm & S_IWOTH) ? 'w' : '-';
    modeval[8] = (perm & S_IXOTH) ? 'x' : '-';
    modeval[9] = '\0';
    return modeval;
}
