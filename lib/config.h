#ifndef CONFIG_H
#define CONFIG_H

class IConfig {
    public:
        virtual ~IConfig() {}
        virtual void OverrideMe() = 0;
};

class Config {
    public:
        Config();
        virtual ~Config();

    private:
};

#endif // CONFIG_H
