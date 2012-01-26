CC = gcc
INPUT_SENDER = udp_sender.c
INPUT_SERVER = udp_server.c
OUTPUT_SENDER = udp_sender
OUTPUT_SERVER = udp_server
PARAMS = -g -O1 -Wall
INCLUDE_DIR = ./include/

all:
	${CC} ${PARAMS} -I${INCLUDE_DIR} ${INPUT_SENDER} -o ${OUTPUT_SENDER}
	${CC} ${PARAMS} -I${INCLUDE_DIR} ${INPUT_SERVER} -o ${OUTPUT_SERVER}	 

clean:
	rm -rf ${OUTPUT_SENDER} ${OUTPUT_SERVER}
