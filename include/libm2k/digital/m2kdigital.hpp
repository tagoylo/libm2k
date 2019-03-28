/*
 * Copyright 2018 Analog Devices, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file LICENSE.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef M2KDIGITAL_HPP
#define M2KDIGITAL_HPP

#include <libm2k/m2kglobal.hpp>
#include <libm2k/digital/genericdigital.hpp>
#include <libm2k/analog/m2khardwaretrigger.hpp>
#include <libm2k/utils/device.hpp>
#include <string>
#include <vector>

using namespace libm2k::devices;
using namespace libm2k::utils;

namespace libm2k {
namespace digital {
class LIBM2K_API M2kDigital : public Device
{
public:
	enum DIO_CHANNEL {
		DIO_CHANNEL_0 = 0,
		DIO_CHANNEL_1 = 1,
		DIO_CHANNEL_2 = 2,
		DIO_CHANNEL_3 = 3,
		DIO_CHANNEL_4 = 4,
		DIO_CHANNEL_5 = 5,
		DIO_CHANNEL_6 = 6,
		DIO_CHANNEL_7 = 7,
		DIO_CHANNEL_8 = 8,
		DIO_CHANNEL_9 = 9,
		DIO_CHANNEL_10 = 10,
		DIO_CHANNEL_11 = 11,
		DIO_CHANNEL_12 = 12,
		DIO_CHANNEL_13 = 13,
		DIO_CHANNEL_14 = 14,
		DIO_CHANNEL_15 = 15,
	};

	enum DIO_MODE {
		DIO_OPENDRAIN = 0,
		DIO_PUSHPULL = 1,
	};

	enum DIO_TRIGGER_MODE {
		DIO_OR = 0,
		DIO_AND = 1,
	};

	enum DIO_DIRECTION {
		DIO_INPUT = 0,
		DIO_OUTPUT = 1,
	};

	enum level {
		LOW = 0,
		HIGH = 1,
	};

	struct channel {
		struct iio_channel* m_channel;
		DIO_DIRECTION m_direction;

	};

	M2kDigital(struct iio_context* ctx, std::string logic_dev);
	virtual ~M2kDigital();

	void setDirection(unsigned short mask);
	void setDirection(unsigned int index, DIO_DIRECTION dir);
	void setDirection(unsigned int index, bool dir);
	void setDirection(DIO_CHANNEL index, bool dir);
	void setDirection(DIO_CHANNEL index, DIO_DIRECTION dir);
	DIO_DIRECTION getDirection(DIO_CHANNEL index);

	void setValueRaw(DIO_CHANNEL index, level);
	level getValueRaw(DIO_CHANNEL index);

	void push(std::vector<short>& data);
	void stop();

	std::vector<unsigned short> getSamples(int nb_samples);

	void enableChannelIn(DIO_CHANNEL index, bool enable);
	void enableChannelOut(DIO_CHANNEL index, bool enable);
	void enableAllIn(bool enable);
	void enableAllOut(bool enable);

	bool anyChannelEnabled(DIO_DIRECTION dir);

	void setTrigger(DIO_CHANNEL, libm2k::analog::M2kHardwareTrigger::condition);
	libm2k::analog::M2kHardwareTrigger::condition getTrigger(DIO_CHANNEL);

	void setTriggerDelay(int delay);
	int getTriggerDelay();

	void setTriggerMode(DIO_TRIGGER_MODE);
	DIO_TRIGGER_MODE getTriggerMode();

	void setOutputMode(DIO_CHANNEL, DIO_MODE);
	DIO_MODE getOutputMode(DIO_CHANNEL);

	bool getCyclic();
	void setCyclic(bool cyclic);
private:
	bool m_cyclic;
	std::shared_ptr<Device> m_dev_read;
	std::shared_ptr<Device> m_dev_write;
	std::string m_dev_name_read;
	std::string m_dev_name_write;
	static std::vector<std::string> m_output_mode;
	static std::vector<std::string> m_trigger_logic_mode;
};
}
}

#endif //M2KDIGITAL_HPP