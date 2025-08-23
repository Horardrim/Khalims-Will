#ifndef HDM_REGISTER_HXX
#define HDM_REGISTER_HXX

class HdmRegister
{
public:
    HdmRegister();

    ~HdmRegister();

    void register();

    void unregister();

    void heartbeat();

private:
    const std::string registerCenterUrl_;
};

#endif
