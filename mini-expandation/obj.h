/* Register definitions */
#define R_UNDEF -1    /* Undefined register */
#define R_FLAG 0      /* Flag register */
#define R_IP 1        /* Instruction pointer */
#define R_BP 2        /* Base pointer */
#define R_JP 3        /* Jump pointer */
#define R_TP 4        /* Top pointer */
#define R_GEN 5       /* General purpose register start */
#define R_NUM 64      /* Total number of registers */

/* Stack frame offsets */
#define FORMAL_OFF -4 	/* Offset for first formal parameter */
#define OBP_OFF 0 		/* Offset for old base pointer (dynamic chain) */
#define RET_OFF 4 		/* Offset for return address */
#define LOCAL_OFF 8 	/* Offset for local variables */

/* Register modification states */
#define MODIFIED 1     /* Register has been modified */
#define UNMODIFIED 0   /* Register has not been modified */

/* Register descriptor structure */
struct rdesc 
{
    struct sym *var;  /* Variable stored in register */
    int mod;          /* Modification status */
};

/* Global variables for stack management */
extern int tos;  /* Top of static memory area */
extern int tof;  /* Top of frame */
extern int oof;  /* Offset of formal parameters */
extern int oon;  /* Offset of next parameter */

/**
 * Translate TAC to assembly code
 */
void tac_obj();
