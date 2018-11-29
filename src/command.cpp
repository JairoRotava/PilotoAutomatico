/*
 * commands.cpp
 *
 * Contem os comandos aceitos pela serial
 */ 

#include <Arduino.h>
#include "./SerialCommand/SerialCommand.h"

SerialCommand sCmd;					// Objeto para tratamento de comandos serial

bool is_valid_int(const char *str);
bool is_valid_flt(const char *str);
void cmdTemplateOneArgDouble(double * variable, double min, double max);
void cmdTemplateOneArgBoolean(boolean * variable);
void cmdTemplateOneArgInt(int * variable, double min, double max);

/*
//void cmdBorboletaSetpoint(void);
void cmdBorboletaSetpoint() {cmdTemplateOneArgDouble(&parametros.setpoint,MIN_BORBOLETA_SETPOINT, MAX_BORBOLETA_SETPOINT);}
void cmdLambdaSetpoint() {cmdTemplateOneArgDouble(&parametros.lambda_setpoint,MIN_V_LAMBDA,MAX_V_LAMBDA);}
void cmdManualMode(void);
void cmdAutoMode(void);
void cmdBangBangOut() {cmdTemplateOneArgDouble(&parametros.bangbang_out,MIN_BANGBANG_OUT, MAX_BANGBANG_OUT);updateConfig();}
void cmdBangBangError() {cmdTemplateOneArgDouble(&parametros.bangbang_error,MIN_BANGBANG_ERROR, MAX_BANGBANG_ERROR);updateConfig();}
void cmdPidBorboletaKI() {cmdTemplateOneArgDouble(&parametros.KI,BORBOLETA_KI_MIN, BORBOLETA_KI_MAX );updateConfig();}
void cmdPidBorboletaKP() {cmdTemplateOneArgDouble(&parametros.KP,BORBOLETA_KP_MIN, BORBOLETA_KP_MAX );updateConfig();}
void cmdPidBorboletaKD() {cmdTemplateOneArgDouble(&parametros.KD,BORBOLETA_KD_MIN, BORBOLETA_KD_MAX );updateConfig();}
void cmdPidLambdaKI() {cmdTemplateOneArgDouble(&parametros.lambda_KI,LAMBDA_KI_MIN, LAMBDA_KI_MAX );updateConfig();}
void cmdPidLambdaKP() {cmdTemplateOneArgDouble(&parametros.lambda_KP,LAMBDA_KP_MIN, LAMBDA_KP_MAX );updateConfig();}
void cmdPidLambdaKD() {cmdTemplateOneArgDouble(&parametros.lambda_KD,LAMBDA_KD_MIN, LAMBDA_KD_MAX );updateConfig();}

void cmdDelayAutoLambda() {cmdTemplateOneArgDouble(&parametros.auto_delay_s,MIN_DELAY_S, MAX_DELAY_S );updateConfig();}
void cmdLambdaMaxBorboleta() {cmdTemplateOneArgDouble(&parametros.auto_borboleta_max,AUTO_BORBOLETA_MAX_MIN, AUTO_BORBOLETA_MAX_MAX );updateConfig();}
void cmdLambdaMinBorboleta() {cmdTemplateOneArgDouble(&parametros.auto_borboleta_min,AUTO_BORBOLETA_MIN_MIN, AUTO_BORBOLETA_MIN_MAX );updateConfig();}
void cmdDelayCombustivelAuxiliar() {cmdTemplateOneArgInt(&parametros.combustivel_aux_delay,COMBUSTIVEL_AUX_MIN_DELAY_S, COMBUSTIVEL_AUX_MAX_DELAY_S );updateConfig();}
void cmdDelayAquecedorLambda() {cmdTemplateOneArgInt(&parametros.lambda_heater_delay,LAMBDA_HEATER_MIN_DELAY_S, LAMBDA_HEATER_MAX_DELAY_S );updateConfig();}
void cmdLambdaVmin() {cmdTemplateOneArgDouble(&parametros.vmin_lambda,VLAMBDA_MIN,VLAMBDA_MAX);updateConfig();}
void cmdLambdaVmax() {cmdTemplateOneArgDouble(&parametros.vmax_lambda,VLAMBDA_MIN,VLAMBDA_MAX);updateConfig();}
void cmdSensorPartidaInverte() {cmdTemplateOneArgBoolean(&parametros.sensor_partida_inv);updateConfig();}
void cmdSensorOperacaoInverte() {cmdTemplateOneArgBoolean(&parametros.sensor_operacao_inv);updateConfig();}
void cmdReset(void);

void cmdEnviaStatusContinuo() {cmdTemplateOneArgBoolean(&envia_dados_continuo);updateConfig();}
*/
void unrecognized(const char *command) {Serial.println("err");}

void addSerialCommands()
{
	/*
	sCmd.addCommand("bsp",cmdBorboletaSetpoint);		// Altera setpoint
	sCmd.addCommand("lsp",cmdLambdaSetpoint);			// Altera setpoint
	sCmd.addCommand("manual",cmdManualMode);			// Controle posicao borboleta
	sCmd.addCommand("auto",cmdAutoMode);				// Controle lambda. Automatico
	sCmd.addCommand("bbo",cmdBangBangOut);				//Seta tamanho da saida do controle bangbgan
	sCmd.addCommand("bbe",cmdBangBangError);				//Seta tamanho do erro/histeres do controle bangbgan
	sCmd.addCommand("bki",cmdPidBorboletaKI);
	sCmd.addCommand("bkp",cmdPidBorboletaKP);
	sCmd.addCommand("bkd",cmdPidBorboletaKD);
	sCmd.addCommand("lki",cmdPidLambdaKI);
	sCmd.addCommand("lkp",cmdPidLambdaKP);
	sCmd.addCommand("lkd",cmdPidLambdaKD);

	sCmd.addCommand("dal",cmdDelayAutoLambda);
	sCmd.addCommand("lminb",cmdLambdaMinBorboleta);
	sCmd.addCommand("lmaxb",cmdLambdaMaxBorboleta);
	sCmd.addCommand("dcombaux",cmdDelayCombustivelAuxiliar);
	sCmd.addCommand("daql",cmdDelayAquecedorLambda);
	sCmd.addCommand("lvmin",cmdLambdaVmin);
	sCmd.addCommand("lvmax",cmdLambdaVmax);
	sCmd.addCommand("spi",cmdSensorPartidaInverte);
	sCmd.addCommand("soi",cmdSensorOperacaoInverte);
	
	
	sCmd.addCommand("reset",cmdReset);
	sCmd.addCommand("esc",cmdEnviaStatusContinuo);	//Habilita o envio de dados continuamente
	*/

	sCmd.setDefaultHandler(unrecognized);      // Handler for command that isn't matched  (says "What?")
	
	
}

void handlerSerialCommands()
{
	sCmd.readSerial();
}

void cmdTemplateOneArgDouble(double * variable, double min, double max)
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		if (*arg == '?')
		{
			Serial.println(*variable);
			return;
		}
		if (is_valid_flt(arg))
		{
			double temp = strtod(arg, NULL);
			if ((temp <= max) && (temp >= min))
			{	//Dentro do range
				*variable = temp;
				Serial.println(*variable);
				return;
			}
		}
		Serial.println("err");	//Erro no comando
	}	
}

void cmdTemplateOneArgInt(int * variable, double min, double max)
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		if (*arg == '?')
		{
			Serial.println(*variable);
			return;
		}
		if (is_valid_flt(arg))
		{
			double temp = strtod(arg, NULL);
			if ((temp <= max) && (temp >= min))
			{	//Dentro do range
				*variable = temp;
				Serial.println(*variable);
				return;
			}
		}
		Serial.println("err");	//Erro no comando
	}
}


void cmdTemplateOneArgBoolean(boolean * variable)
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		if (*arg == '?')
		{
			Serial.println(*variable);
			return;
		}
		if (*arg == '1')
		{
			*variable = true;
			Serial.println(*variable);
			return;
		}
		if (*arg == '0')
		{
			*variable = false;
			Serial.println(*variable);
			return;
		}
		Serial.println("err");	//Erro no comando
	}
}


// Altera setpoint borboleta
//void cmdBorboletaSetpoint() {cmdTemplateOneArgDouble(&parametros.setpoint,0., 100.);}
/*
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL) 
	{
		if (*arg == '?')
		{
			Serial.println(parametros.setpoint);
			return;
		}
		if (is_valid_flt(arg))
		{
			parametros.setpoint = strtod(arg, NULL);		
			Serial.println(parametros.setpoint);
			return;
		}
		Serial.println("erro");
	}
}


// Altera setpoint lambda
void cmdLambdaSetpoint()
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		parametros.lambda_setpoint = strtod(arg, NULL);
	}
}
*/


/*
void cmdBangBangOut(void)
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		parametros.bangbang_out  = strtod(arg, NULL);
		updateConfig();
	}
}

void cmdBangBangError(void)
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		parametros.bangbang_error = strtod(arg, NULL);
		updateConfig();
	}
}

void cmdPidBorboletaKI(void)
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		parametros.KI = strtod(arg, NULL);
		updateConfig();
	}
}

void cmdPidBorboletaKP(void)
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		parametros.KP = strtod(arg, NULL);
		updateConfig();
	}
}

void cmdPidBorboletaKD(void)
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		parametros.KD = strtod(arg, NULL);
		updateConfig();
	}
}

void cmdPidLambdaKI(void)
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		parametros.lambda_KI = strtod(arg, NULL);
		updateConfig();
	}
}

void cmdPidLambdaKP(void)
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		parametros.lambda_KP = strtod(arg, NULL);
		updateConfig();
	}
}

void cmdPidLambdaKD(void)
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		parametros.lambda_KD = strtod(arg, NULL);
		updateConfig();
	}
}

// delay para entrar em lambda
void cmdDelayAutoLambda()
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		parametros.auto_delay_s = strtod(arg, NULL);
		updateConfig();
	}
}

void cmdLambdaMaxBorboleta()
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		parametros.auto_borboleta_max = strtod(arg, NULL);
		updateConfig();
	}
}

void cmdLambdaMinBorboleta()
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		parametros.auto_borboleta_min = strtod(arg, NULL);
		updateConfig();
	}
}

void cmdDelayCombustivelAuxiliar()
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		parametros.combustivel_aux_delay = strtod(arg, NULL);
		updateConfig();
	}
}


void cmdDelayAquecedorLambda()
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		parametros.lambda_heater_delay = strtod(arg, NULL);
		updateConfig();
	}
}

void cmdLambdaVmin()
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		parametros.vmin_lambda = strtod(arg, NULL);
		updateConfig();
	}
}

void cmdLambdaVmax()
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		parametros.vmax_lambda = strtod(arg, NULL);
		updateConfig();
	}
}

	
void cmdSensorPartidaInverte()
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		parametros.sensor_partida_inv = strtod(arg, NULL);
		updateConfig();
	}
}

void cmdSensorOperacaoInverte()
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		parametros.sensor_operacao_inv = strtod(arg, NULL);
		updateConfig();
	}
}
*/
void(* softReset)(void) = 0;	//Pula para inicio do programa. soft reset

void cmdReset()
{	//Reset com wdt nao funciona por causa do bootloader
	softReset();
}

/*
void cmdEnviaStatusContinuo()
{
	char *arg;
	arg = sCmd.next();
	if (arg != NULL)
	{
		envia_dados_continuo = strtod(arg, NULL);
		updateConfig();
	}
}

*/

bool is_valid_int(const char *str)
{
	// Handle negative numbers.
	//
	if (*str == '-')
	++str;

	// Handle empty string or just "-".
	//
	if (!*str)
	return false;

	// Check for non-digit chars in the rest of the stirng.
	//
	while (*str)
	{
		if (!isdigit(*str))
		return false;
		else
		++str;
	}

	return true;
}



bool is_valid_flt(const char *str)
{
	// Handle negative numbers.
	//
	if (*str == '-')
	++str;
	
	// Handle negative numbers.
	//
	if (*str == '+')
	++str;


	// Handle empty string or just "-".
	//
	if (!*str)
	return false;

	// Check for non-digit chars in the rest of the string.
	//
	while (*str)
	{
		if (!isdigit(*str) && (*str!='.'))
		return false;
		else
		++str;
	}

	return true;
}
