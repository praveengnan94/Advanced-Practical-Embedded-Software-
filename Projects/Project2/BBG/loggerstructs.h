typedef enum {
  magneto_Task,
  uv_Task,
  pressure_Task,
  error_handler
}task_type;

typedef struct{
char time_stamp[32];
task_type log_source;
char log_msg[BUFFER_SIZE -100];
uint8_t log_level;
}logger_pckt;