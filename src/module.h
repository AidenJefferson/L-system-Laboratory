#ifndef MODULE_H
#define MODULE_H

#include <vector>
#include <ostream>

namespace Modules {

    // represents Master module
    class Module {
    public:
        Module(void)
        {
        }

        ~Module(void)
        {
        }

        virtual void render(void) = 0;
        virtual void print(void) = 0;
        virtual char type(void) = 0;
        virtual double value1(void) { return 0; }
        virtual double value2(void) { return 0; }
    };

    // forward module, F in turtle representation
    class Forward : public Module {
    public:

        Forward(double l)
            : Type{ 'F' }, Length{ l }
        {
        }

        void render(void) override;
        void print(void) override;

        char type(void) override;
        double value1(void) override;

    private:
        char Type;
        double Length;
    };

    // no forward module, f in turtle representation
    class NoForward : public Module {
    public:
        NoForward(double l)
            : Type{ 'f' }, Length{ l }
        {
        }

        void render(void) override;
        void print(void) override;
        char type(void) override;
        double value1(void) override;

    private:
        char Type;
        double Length;
    };

    // turn left module, + in turtle representation
    class LeftTurn : public Module {
    public:
        LeftTurn(double a)
            : Type{ '+' }, Angle{ a }
        {
        }

        void render(void) override;
        void print(void) override;
        char type(void) override;
        double value1(void) override;

    private:
        char Type;
        double Angle;
    };

    // turn right module, - in turtle representation
    class RightTurn : public Module {
    public:
        RightTurn(double a)
            : Type{ '-' }, Angle{ a }
        {
        }

        void render(void) override;
        void print(void) override;
        char type(void) override;
        double value1(void) override;

    private:
        char Type;
        double Angle;
    };

    // pitch up module, ^ in turtle representation
    class UpPitch : public Module {
    public:
        UpPitch(double a)
            : Type{ '^' }, Angle{ a }
        {
        }

        void render(void) override;
        void print(void) override;
        char type(void) override;
        double value1(void) override;

    private:
        char Type;
        double Angle;
    };

    // pitch down module, & in turtle representation
    class DownPitch : public Module {
    public:
        DownPitch(double a)
            : Type{ '&' }, Angle{ a }
        {
        }

        void render(void) override;
        void print(void) override;
        char type(void) override;
        double value1(void) override;

    private:
        char Type;
        double Angle;
    };

    // roll left module, \ in turtle representation
    class LeftRoll : public Module {
    public:
        LeftRoll (double a)
            : Type{ '<' }, Angle{ a }
        {
        }

        void render(void) override;
        void print(void) override;
        char type(void) override;
        double value1(void) override;

    private:
        char Type;
        double Angle;
    };

    // roll right module, / in turtle representation
    class RightRoll : public Module {
    public:
        RightRoll(double a)
            : Type{ '>' }, Angle{ a }
        {
        }

        void render(void) override;
        void print(void) override;
        char type(void) override;
        double value1(void) override;

    private:
        char Type;
        double Angle;
    };

    // set virtical module, $ in turtle representation
    class Virtical : public Module {
    public:
        Virtical(void)
            : Type{ '$' }
        {
        }

        void render(void) override;
        void print(void) override;
        char type(void) override;

    private:
        char Type;
    };

    // start branch module, [ in turtle representation
    class StartBranch : public Module {
    public:
        StartBranch(void)
            : Type{ '[' }
        {
        }

        void render(void) override;
        void print(void) override;
        char type(void) override;

    private:
        char Type;
    };

    // end branch module, ] in turtle representation
    class EndBranch : public Module {
    public:
        EndBranch(void)
            : Type{ ']' }
        {
        }

        void render(void) override;
        void print(void) override;
        char type(void) override;

    private:
        char Type;
    };

    // set width module, ! in turtle representation
    class SetWidth : public Module {
    public:
        SetWidth(double w)
            : Type{ '!' }, Width{ w }
        {
        }

        void render(void) override;
        void print(void) override;
        char type(void) override;
        double value1(void) override;

    private:
        char Type;
        double Width;
    };

    // placer module, X in turtle representation (X can be any letter not already used)
    class Placer : public Module {
    public:
        Placer(char c, double l, double w)
            : Type{ c }, Length{ l }, Width{ w }
        {
        }

        void render(void) override;
        void print(void) override;
        char type(void) override;
        double value1(void) override;
        double value2(void) override;

    private:
        char Type;
        double Length;
        double Width;
    };

    struct Render_Info{

        double Render_Width = 0.1;
        std::vector<double> Temp_Render_Width = {0.1};
        std::vector<double> rotation_current = {0,0,0}; // turn, pitch, roll
        std::vector<std::vector<double>> rotation_branch; // turn, pitch, roll
    };

    // helper function
    void reset_render_info(void);

}

#endif // MODULE_H
