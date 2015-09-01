
#ifndef LIS3MDL_H
#define LIS3MDL_H

#define LIS3MDL_TWI_ADDRESS 0b0011100

class LIS3MDL_TWI
{
    public:
        LIS3MDL_TWI(uint8_t addr = LIS3MDL_TWI_ADDRESS);

        void begin();

        int16_t readX();
        int16_t readY();
        int16_t readZ();

    private:
        uint8_t _addr;
        uint8_t _ctrlReg1;

    protected:
        void writeCtrlReg1();
        int16_t readAxis(uint8_t reg);
};

#endif
