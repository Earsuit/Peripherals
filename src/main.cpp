// #include <spdlog/spdlog.h>
// #include <unistd.h>
// #include <iostream>

// //MPU9250
// #define MPU9250_AD (uint8_t)0x69
// #define FIFO_EN_AD (uint8_t)0x23
// #define PWR_MGMT_1_AD (uint8_t)0x6B
// #define ACCEL_XOUT_H_AD (uint8_t)0x3B
// #define GYRO_XOUT_H_AD (uint8_t)0x43
// #define EXT_SENS_DATA_00_AD (uint8_t)0x49
// #define ACCEL_CONFIG_1_AD (uint8_t)0x1C
// #define ACCEL_CONFIG_2_AD (uint8_t)0x1D
// #define GYRO_CONFIG_AD (uint8_t)0x1B
// #define CONFIG_AD (uint8_t)0x1A
// #define I2C_MST_CTRL_AD (uint8_t)0x24
// #define I2C_SLV0_ADDR_AD (uint8_t)0x25
// #define I2C_SLV0_REG_AD (uint8_t)0x26
// #define I2C_SLV0_CTRL_AD (uint8_t)0x27
// #define INT_BYPASS_CONFIG_AD (uint8_t)0x37
// #define USER_CTRL_AD (uint8_t)0x6A
// #define ACCEL_SENS 8192.0f
// #define GYRO_SENS 131.0f

// //Magnetometer
// #define MAG_AD 0xC
// #define WIA_AD 0x00
// #define INFO 0x01
// #define STATUS_1_AD 0x02
// #define HXL_AD 0x03    //X-axis measurement data lower 8bit
// #define HXH_AD 0x04    //X-axis measurement data higher 8bit
// #define HYL_AD 0x05    //Y-axis measurement data lower 8bit
// #define HYH_AD 0x06    //Y-axis measurement data higher 8bit
// #define HZL_AD 0x07    //Z-axis measurement data lower 8bit
// #define HZH_AD 0x08    //Z-axis measurement data higher 8bit
// #define STATUS_2_AD 0x09
// #define CNTL1_AD 0x0A   //control 1
// #define CNTL2_AD 0x0B   //control 2
// #define ASTC_AD 0x0C    //Self-Test Control
// #define TS1_AD 0x0D    //test 1
// #define TS2_AD 0x0E   //test 2
// #define I2CDIS_AD 0x0F    //I2C disable
// #define ASAX_AD 0x10    //Magnetic sensor X-axis sensitivity adjustment value
// #define ASAY_AD 0x11    //Magnetic sensor Y-axis sensitivity adjustment value
// #define ASAZ_AD 0x12    //Magnetic sensor Z-axis sensitivity adjustment value
// #define MAGNE_SENS 6.67f
// #define SCALE 0.1499f  // 4912/32760 uT/tick
// #define DATA_READY 0x01
// #define MAGIC_OVERFLOW 0x8

// void MPU9250Setup();
// void readGyro();

// volatile float accelX,accelY,accelZ,gyroX,gyroY,gyroZ,magneX,magneY,magneZ,asax,asay,asaz;
// BSC i2c;
// using std::cout;
// using std::endl;

// namespace spd = spdlog;
// int main(int argc,char* argv[]){
//     // i2c.I2Csetup(100);
//     auto console = spd::stdout_color_mt("console");
//     console->info("Welcome to spdlog!");
//     // MPU9250Setup();
//     // cout<<"here"<<endl;
//     // sleep(10);
//     // readGyro();
//     // cout<<accelX<<endl;
//     return 0;
// }

// void MPU9250Setup(){
//     {uint8_t data[2] = {PWR_MGMT_1_AD,0x01};
//     i2c.write(MPU9250_AD,2,data);}

//     {uint8_t data[2] = {ACCEL_CONFIG_1_AD,0x08};
//     i2c.write(MPU9250_AD,2,data);}

//     {uint8_t data[2] = {ACCEL_CONFIG_2_AD,0x05};
//     i2c.write(MPU9250_AD,2,data);}

//     {uint8_t data[2] = {GYRO_CONFIG_AD,0x08};
//     i2c.write(MPU9250_AD,2,data);}

//     {uint8_t data[2] = {CONFIG_AD,0x05};
//     i2c.write(MPU9250_AD,2,data);}
// }

// void readGyro(){
//     //read the accelerate
//     i2c.request(MPU9250_AD,ACCEL_XOUT_H_AD,6);

//     accelX = (i2c.readBuffer()<<8) | i2c.readBuffer();
//     accelY = (i2c.readBuffer()<<8) | i2c.readBuffer();
//     accelZ = (i2c.readBuffer()<<8) | i2c.readBuffer();

//     //read the gyro
//     i2c.request(MPU9250_AD,GYRO_XOUT_H_AD,6);
//     gyroX = (i2c.readBuffer()<<8) | i2c.readBuffer();
//     gyroY = (i2c.readBuffer()<<8) | i2c.readBuffer();
//     gyroZ = (i2c.readBuffer()<<8) | i2c.readBuffer();
// }


#include "spdlog/spdlog.h"

#include <iostream>
#include <memory>

void async_example();
void syslog_example();
void user_defined_example();
void err_handler_example();

namespace spd = spdlog;
int main(int, char*[])
{
    try
    {
        // Console logger with color
        auto console = spd::stdout_color_mt("console");
        console->info("Welcome to spdlog!");
        console->error("Some error message with arg{}..", 1);
	
        // Formatting examples
        console->warn("Easy padding in numbers like {:08d}", 12);
        console->critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
        console->info("Support for floats {:03.2f}", 1.23456);
        console->info("Positional args are {1} {0}..", "too", "supported");
        console->info("{:<30}", "left aligned");
	
	// Use global registry to retrieve loggers
        spd::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(logger_name) function");
        
        // Create basic file logger (not rotated)
        auto my_logger = spd::basic_logger_mt("basic_logger", "logs/basic.txt");
        my_logger->info("Some log message");

        // Create a file rotating logger with 5mb size max and 3 rotated files
        auto rotating_logger = spd::rotating_logger_mt("some_logger_name", "logs/mylogfile.txt", 1048576 * 5, 3);
        for (int i = 0; i < 10; ++i)
            rotating_logger->info("{} * {} equals {:>10}", i, i, i*i);

        // Create a daily logger - a new file is created every day on 2:30am
        auto daily_logger = spd::daily_logger_mt("daily_logger", "logs/daily.txt", 2, 30);
        // trigger flush if the log severity is error or higher
        daily_logger->flush_on(spd::level::err);
        daily_logger->info(123.44);

        // Customize msg format for all messages
        spd::set_pattern("[%^+++%$] [%H:%M:%S %z] [thread %t] %v");
        console->info("This an info message with custom format (and custom color range between the '%^' and '%$')");
	console->error("This an error message with custom format (and custom color range between the '%^' and '%$')");

        // Runtime log levels
	spd::set_level(spd::level::info); //Set global log level to info
	console->debug("This message should not be displayed!");
	console->set_level(spd::level::debug); // Set specific logger's log level
	console->debug("This message should be displayed..");

        // Compile time log levels
        // define SPDLOG_DEBUG_ON or SPDLOG_TRACE_ON
        SPDLOG_TRACE(console, "Enabled only #ifdef SPDLOG_TRACE_ON..{} ,{}", 1, 3.23);
        SPDLOG_DEBUG(console, "Enabled only #ifdef SPDLOG_DEBUG_ON.. {} ,{}", 1, 3.23);

        // Asynchronous logging is very fast..
        // Just call spdlog::set_async_mode(q_size) and all created loggers from now on will be asynchronous..
        async_example();

        // syslog example. linux/osx only
        syslog_example();

        // android example. compile with NDK
        android_example();

        // Log user-defined types example
        user_defined_example();

        // Change default log error handler
        err_handler_example();

        // Apply a function on all registered loggers
        spd::apply_all([&](std::shared_ptr<spd::logger> l)
        {
            l->info("End of example.");
        });

        // Release and close all loggers
        spd::drop_all();
    }
    // Exceptions will only be thrown upon failed logger or sink construction (not during logging)
    catch (const spd::spdlog_ex& ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
        return 1;
    }
}

void async_example()
{
    size_t q_size = 4096; 
    spd::set_async_mode(q_size);
    auto async_file = spd::daily_logger_st("async_file_logger", "logs/async_log.txt");
    for (int i = 0; i < 100; ++i)
        async_file->info("Async message #{}", i);
}

//syslog example
void syslog_example()
{
#ifdef SPDLOG_ENABLE_SYSLOG 
    std::string ident = "spdlog-example";
    auto syslog_logger = spd::syslog_logger("syslog", ident, LOG_PID);
    syslog_logger->warn("This is warning that will end up in syslog..");
#endif
}

// user defined types logging by implementing operator<<
struct my_type
{
    int i;
    template<typename OStream>
    friend OStream& operator<<(OStream& os, const my_type &c)
    {
        return os << "[my_type i="<<c.i << "]";
    }
};

#include <spdlog/fmt/ostr.h> // must be included
void user_defined_example()
{
    spd::get("console")->info("user defined type: {}", my_type { 14 });
}

//
//custom error handler
//
void err_handler_example()
{	
	spd::set_error_handler([](const std::string& msg) {
		std::cerr << "my err handler: " << msg << std::endl;
	}); 
	// (or logger->set_error_handler(..) to set for specific logger)
}
