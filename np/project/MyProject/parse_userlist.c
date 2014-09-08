void parse
(char *userlist_str)
{
    char *pch = strtok (userlist_str, "|")
        while (pch != NULL) {
            int user_id, user_sockfd;
            char username[64];
            sscanf(pch, "%d,%d,%s", &user_id, &user_sockfd, username);
            pch = strtok (NULL, "|");
        }
}
