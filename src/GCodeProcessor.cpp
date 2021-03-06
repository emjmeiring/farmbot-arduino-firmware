/*
 * GCodeProcessor.cpp
 *
 *  Created on: 15 maj 2014
 *      Author: MattLech
 *      Author: Tim Evers
 */

#include "GCodeProcessor.h"
#include "CurrentState.h"

GCodeProcessor::GCodeProcessor() {

}

GCodeProcessor::~GCodeProcessor() {
}

void GCodeProcessor::printCommandLog(Command* command) {
	Serial.print("command == NULL:");
	Serial.println(command == NULL);
	Serial.println("command->getCodeEnum() == CODE_UNDEFINED:");
	Serial.println(command->getCodeEnum() == CODE_UNDEFINED);
}

int GCodeProcessor::execute(Command* command) {
	long Q = command->getQ();
	//Q = 99;
	CurrentState::getInstance()->setQ(Q);

	if(command == NULL || command->getCodeEnum() == CODE_UNDEFINED) {
		if(LOGGING) {
			printCommandLog(command);
		}
		return -1;
	}
	GCodeHandler* handler = getGCodeHandler(command->getCodeEnum());
	if(handler == NULL) {
		Serial.println("R99 This is false: handler == NULL");
		return -1;
	}
	Serial.print(COMM_REPORT_CMD_START);
	CurrentState::getInstance()->printQAndNewLine();
	//Serial.print(" Q");
	//Serial.print(Q);
	//Serial.print("\n\r");

	int execution = handler->execute(command);
	if(execution == 0) {
		Serial.print(COMM_REPORT_CMD_DONE);
		CurrentState::getInstance()->printQAndNewLine();
		//Serial.print(" Q");
		//Serial.print(Q);
		//Serial.print("\n\r");
	} else {
		Serial.print(COMM_REPORT_CMD_ERROR);
		CurrentState::getInstance()->printQAndNewLine();
		//Serial.print(" Q");
		//Serial.print(Q);
		//Serial.print("\n\r");
	}

	CurrentState::getInstance()->resetQ();
	return execution;
};

GCodeHandler* GCodeProcessor::getGCodeHandler(CommandCodeEnum codeEnum) {
	switch(codeEnum) {
	case G00:
		return G00Handler::getInstance();
	case G28:
		return G28Handler::getInstance();

	case F11:
		return F11Handler::getInstance();
	case F12:
		return F12Handler::getInstance();
	case F13:
		return F13Handler::getInstance();

	case F14:
		return F14Handler::getInstance();
	case F15:
		return F15Handler::getInstance();
	case F16:
		return F16Handler::getInstance();

	case F20:
		return F20Handler::getInstance();
	case F21:
		return F21Handler::getInstance();
	case F22:
		return F22Handler::getInstance();

	case F31:
		return F31Handler::getInstance();
	case F32:
		return F32Handler::getInstance();


	case F41:
		return F41Handler::getInstance();
	case F42:
		return F42Handler::getInstance();
	case F43:
		return F43Handler::getInstance();
	case F44:
		return F44Handler::getInstance();

	case F61:
		return F61Handler::getInstance();

	case F81:
		return F81Handler::getInstance();
	case F82:
		return F82Handler::getInstance();
	case F83:
		return F83Handler::getInstance();
	}
	return NULL;
}


