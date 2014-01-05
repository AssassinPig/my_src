int my_c_function(const char* from_py)
{
    printf("from python is %s\n", from_py);
    if(strcmp(from_py, "yes"))
        return 0;
    else if(strcmp(from_py, "no"))
        return 1;
    else 
        return 9999;
}
