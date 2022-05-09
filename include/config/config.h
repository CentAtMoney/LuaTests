// config.h
#ifndef CONFIG_CONFIG_H
#define CONFIG_CONFIG_H

#include "common.h"
#include <exception>

/**
 * @brief exception to indicate key in config is invalid (can't be encoded, key is not mapped, etc.)
 */
class bad_key_error : public std::runtime_error
{
public:
    bad_key_error(const std::string& what) :
        runtime_error(what)
    {
    }
};


/**
 * @brief Interface for externally retrieving values
 */
class read_config
{
public:
    virtual ~read_config() {}
    virtual std::string get_string(const std::string& name) = 0;
    virtual int get_int(const std::string& name) = 0;
    virtual bool get_bool(const std::string& name) = 0;
};

/**
 * @brief Interface for externally storing values
 */
class write_config
{
public:
    virtual ~write_config() {}
    virtual void set_string(const std::string& name, const std::string& value) = 0;
    virtual void set_int(const std::string& name, int value) = 0;
    virtual void set_bool(const std::string& name, bool value) = 0;
};

/**
 * @brief Interface for externally retrieving and storing values
 */
class config : public read_config, write_config
{
public:

};

#endif // CONFIG_CONFIG_H