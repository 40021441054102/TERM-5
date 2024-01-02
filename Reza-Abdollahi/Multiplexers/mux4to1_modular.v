//-- Mux 2 to 1
module mux2x1(i1, i0, sel, f);
    input i1, i0, sel;
    output f;
    not(nsel, sel);
    and(a, i0, nsel);
    and(b, i1, sel);
    or (f, a, b);
endmodule

//-- Mux 4 to 1
module mux4x1(i3, i2, i1, i0, sel1, sel0, f);
    input i3, i2, i1, i0, sel1, sel0;
    output f;
    wire f1, f2;
    mux2x1 m0(
        .i0(i0),
        .i1(i1),
        .sel(sel1),
        .f(f1)
    );
    mux2x1 m1(
        .i0(i2),
        .i1(i3),
        .sel(sel1),
        .f(f2)
    );
    mux2x1 m2(
        .i0(f1),
        .i1(f2),
        .sel(sel0),
        .f(f)
    );
endmodule

//-- Test Bench
module test_mux4x1();
    reg i0, i1, i2, i3, sel0, sel1;
    wire f;
    mux4x1 test(
        .i0(i0),
        .i1(i1),
        .i2(i2),
        .i3(i3),
        .sel0(sel0),
        .sel1(sel1),
        .f(f)
    );
    initial begin
        $monitor("\033[0;36mi0 = %b, i1 = %b, i2 = %b, i3 = %b \033[0m|\033[0;33m s1 = %b, s0 = %b\033[0m | f = %b", i0, i1, i2, i3, sel1, sel0, f);
        sel1 = 1'b0;
        sel0 = 1'b0;
        i0 = 1'b1;
        i1 = 1'b0;
        i2 = 1'b0;
        i3 = 1'b1;
        #10;
        sel1 = 1'b0;
        sel0 = 1'b1;
        #10
        sel1 = 1'b1;
        sel0 = 1'b0;
        #10
        sel1 = 1'b1;
        sel0 = 1'b1;
    end
endmodule