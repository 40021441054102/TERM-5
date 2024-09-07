//-- Mux 2 to 1
module mux2to1 (
    sel, i1, i0, f
);
    input i0, i1, sel;
    output f;
    and(a, i0, nsel);
    and(b, i1, sel);
    not(nsel, sel);
    or (f, a, b);
endmodule

//-- Test Bench
module test_mux2to1();
    reg i0, i1, sel;
    wire f;
    mux2to1 mux(
        .i0(i0),
        .i1(i1),
        .sel(sel),
        .f(f)
    );
    initial begin
        $monitor("\033[0;36mi0 = %b, i1 = %b \033[0m|\033[0;33m sel = %b \033[0m| f = %b", i0, i1, sel, f);
        i0 = 0;
        i1 = 0;
        sel = 0;
        #10;
        i0 = 1;
        i1 = 0;
        sel = 0;
        #10;
        i0 = 0;
        i1 = 1;
        sel = 0;
        #10;
        i0 = 1;
        i1 = 1;
        sel = 0;
        #10;
        i0 = 0;
        i1 = 0;
        sel = 1;
        #10;
        i0 = 1;
        i1 = 0;
        sel = 1;
        #10;
        i0 = 0;
        i1 = 1;
        sel = 1;
        #10;
        i0 = 1;
        i1 = 1;
        sel = 1;
    end
endmodule
