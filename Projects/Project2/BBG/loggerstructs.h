typedef struct{
char time_stamp[32];
char log_msg[BUFFER_SIZE -100];
uint8_t log_level;
}logger_pckt;

// typedef struct{
// 	uint32_t clientid;
// 	uint32_t clientinfo;
// 	float uv_payload;
// 	float pr_payload;
// }uartstructre;