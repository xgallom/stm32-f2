/*
 * Application.cpp
 *
 *  Created on: Jun 17, 2018
 *      Author: xgallom
 */

#include "Application.h"
#include "Util/Timer.h"

LOGGER_MODULE(Application)

Application *Application::m_instance = nullptr;

Application::ApplicationInitializator::ApplicationInitializator(Application *parent)
{
	m_instance = parent;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
}

Application::Application() :
	m_applicationInitializator(this),
	logger(&usartLog),
	usartLog(Periph::Usarts::Usart2, 9600),
	m_appRunningLed(Periph::Leds::Blue),
	m_engine1(Periph::Engines::M3)
{}

void Application::run()
{
	INF_LOG("Application started running.");

	m_appRunningLed.turnOn();

	m_engine1.setTargetSpeed(100);
	m_engine1.setTargetDirection(Periph::Dirs::Forward);

	Util::Timer timer(Util::Time::FromMilliSeconds(500));
	timer.start();

	for(;;) {

		//uint8_t input[256];

		//uint32_t inputSize = usartLog.readLine(input, 256);

		//usartLog.write(input, inputSize);

		if(timer.run())
			m_engine1.update();
	}

	INF_LOG("Application ended.");
}

Application *Application::instance()
{
	return m_instance;
}

