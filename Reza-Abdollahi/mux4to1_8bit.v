module mux2x1(
    i0, i1, sel, f
);
    input i0, i1, sel;
    output f;
    and(a, i0, nsel);
    and(b, i1, sel);
    not(nsel, sel);
    or(f, a, b);
endmodule

module mux4x1(
    i0, i1, i2, i3, sel0, sel1, f
);
    input i0, i1, i2, i3, sel0, sel1;
    output f;
    wire f1, f2;
    mux2x1 m1(.i0(i0), .i1(i1), .sel(sel0), .f(f1));
    mux2x1 m2(.i0(i2), .i1(i3), .sel(sel0), .f(f2));
    mux2x1 m3(.i0(f1), .i1(f2), .sel(sel1), .f(f));
endmodule

module mux4x1_8bit(
    i0, i1, i2, i3, sel0, sel1, f
);
    input [7:0] i0, i1, i2, i3;
    input sel0, sel1;
    output [7:0] f;
    mux4x1 m0(.i0(i0[0]), .i1(i1[0]), .i2(i2[0]), .i3(i3[0]), .sel0(sel0), .sel1(sel1), .f(f[0]));
    mux4x1 m1(.i0(i0[1]), .i1(i1[1]), .i2(i2[1]), .i3(i3[1]), .sel0(sel0), .sel1(sel1), .f(f[1]));
    mux4x1 m2(.i0(i0[2]), .i1(i1[2]), .i2(i2[2]), .i3(i3[2]), .sel0(sel0), .sel1(sel1), .f(f[2]));
    mux4x1 m3(.i0(i0[3]), .i1(i1[3]), .i2(i2[3]), .i3(i3[3]), .sel0(sel0), .sel1(sel1), .f(f[3]));
    mux4x1 m4(.i0(i0[4]), .i1(i1[4]), .i2(i2[4]), .i3(i3[4]), .sel0(sel0), .sel1(sel1), .f(f[4]));
    mux4x1 m5(.i0(i0[5]), .i1(i1[5]), .i2(i2[5]), .i3(i3[5]), .sel0(sel0), .sel1(sel1), .f(f[5]));
    mux4x1 m6(.i0(i0[6]), .i1(i1[6]), .i2(i2[6]), .i3(i3[6]), .sel0(sel0), .sel1(sel1), .f(f[6]));
    mux4x1 m7(.i0(i0[7]), .i1(i1[7]), .i2(i2[7]), .i3(i3[7]), .sel0(sel0), .sel1(sel1), .f(f[7]));
endmodule

module test_mux4x1_8bit();
    reg [7:0] i0, i1, i2, i3;
    reg sel0, sel1;
    wire [7:0] f;
    mux4x1_8bit test(.i0(i0), .i1(i1), .i2(i2), .i3(i3), .sel0(sel0), .sel1(sel1), .f(f));
    initial begin
        $monitor("\033[0;36mi0 = %b, i1 = %b, i2 = %b, i3 = %b \033[0m| sel0 = %b, sel1 = %b | f = %b", i0, i1, i2, i3, sel0, sel1, f);
        sel0 = 1'b0;
        sel1 = 1'b0;
        i0 = 8'b01101100;
        i1 = 8'b11100010;
        i2 = 8'b11001010;
        i3 = 8'b00011010;
        #10
        sel0 = 1'b1;
        #10
        sel0 = 1'b0;
        sel1 = 1'b1;
        #10
        sel0 = 1'b1;
    end
endmodule