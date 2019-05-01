#ifndef ERROR_H
#define ERROR_H
#define TEST 1
/**
 * Error handling macros.
 */
#define ERR_EXIT(err)                           \
        do {                                    \
                perror(err);                    \
                exit(1);                        \
        } while (0)
#define ERR_EXIT_WITH_MSG(err, err_msg)                         \
        do {                                                    \
                fprintf(stderr, "%s: %s\n", err, err_msg);	\
                exit(1);					\
        } while (0)

#endif /* ERROR_H */
