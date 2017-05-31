#include<systemc.h>

SC_MODULE(ADDER_1){
    sc_in< bool > start;
    sc_in< bool > stop;
    sc_in<sc_int<8> > sum_in;
    sc_in<sc_int<8> > i_in;
    sc_out<sc_int<8> > sum_out;

    void count_sum(){
        if(stop.read() == 1){
            sum_out.write(sum_in.read());
        }else if(start.read() == 1){
            sum_out.write(sum_in.read() + i_in.read());
        }
    }

    SC_CTOR(ADDER_1){
        SC_METHOD(count_sum);
        sensitive << i_in;
    }
};

SC_MODULE(ADDER_2){
    sc_in_clk clk;
    sc_in< bool > start;
    sc_in< bool > stop;
    sc_in<sc_int<8> > i_in;
    sc_out<sc_int<8> > i_out;

    void count_i(){
        if(stop.read() == 1){
            i_out.write(i_in.read());
        }else if(start.read() == 1){
            i_out.write(i_in.read() + 1);
        }
    }

    SC_CTOR(ADDER_2){
        SC_METHOD(count_i);
        sensitive << clk.pos();
    }
};

SC_MODULE(CTL_UNIT){
    sc_out< bool >  start_out;
    sc_out< bool >  stop;
    sc_out< bool > outready;
    sc_in< sc_int<8> > i;
    sc_in< sc_int<8> > N;
    sc_in< bool > start_in;
    sc_in_clk clk;

    void control_unit(){
        // cout << N.read() << " " << i.read() << endl;
        if(stop.read() == 1 || N.read() == i.read()){
            start_out.write(0);
            stop.write(1);
            outready.write(1);
            sc_stop();
        }else if(start_in.read() == 1 && stop.read() == 0){
            start_out.write(1);
            stop.write(0);
        }
    }

    SC_CTOR(CTL_UNIT){
        SC_METHOD(control_unit);
        sensitive << clk.pos();
    }
};

int sc_main(int argc, char* argv[]){
    // sc_set_time_resolution(1, SC_US);

    sc_signal< bool > start_out, stop_out, start_in, outready;
    sc_signal< sc_int<8> > i, sum, N_in;
    outready = 0;
    int N;
    cin >> N;

    sc_clock clock;
    ADDER_1 adder_1("ADDER_1");
    ADDER_2 adder_2("ADDER_2");
    CTL_UNIT ctl_unit("CTL_UNIT");

    adder_1.start(start_out);
    adder_1.stop(stop_out);
    adder_1.sum_in(sum);
    adder_1.sum_out(sum);
    adder_1.i_in(i);

    adder_2.start(start_out);
    adder_2.stop(stop_out);
    adder_2.i_in(i);
    adder_2.i_out(i);
    adder_2.clk(clock);

    ctl_unit.start_out(start_out);
    ctl_unit.stop(stop_out);
    ctl_unit.outready(outready);
    ctl_unit.i(i);
    ctl_unit.clk(clock);

    // how to input - start_in, N_in
    N_in = N;
    start_in = 1;
    ctl_unit.N(N_in);
    ctl_unit.start_in(start_in);

    sc_trace_file *wf = sc_create_vcd_trace_file("sumup_wave");
    sc_trace(wf, i, "i");
    sc_trace(wf, sum, "sum");
    sc_trace(wf, clock, "clock");
    sc_trace(wf, start_out, "start");
    sc_trace(wf, stop_out, "stop");
    sc_trace(wf, outready, "outready");

    sc_start();
    cout << "Closing VCD File" << endl;
    sc_close_vcd_trace_file(wf);
    // cout << sum << endl;

    return 0;
}
