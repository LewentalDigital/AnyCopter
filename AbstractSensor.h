class AbstractSensor {
   private:
   public:
    virtual ~AbstractSensor() = default;
    virtual void read() = 0;
};