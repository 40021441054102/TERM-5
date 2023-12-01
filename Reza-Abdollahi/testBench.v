module ex(x, y, z, f);
    input x, y, z;
    output f;
    nor(nor_x_y, x, y);
    xor(xor_x_y, x, y);
    nor(nor_x_z, x, z);
    and(and_a_b, nor_x_y, xor_x_y);
    nor(f, and_a_b, nor_x_z);
endmodule

module test_bench();
    reg x, y, z;
    wire f;
    ex test(.x(x), .y(y), .z(z), .f(f));
    initial begin
        x = 1'b0;
        y = 1'b0;
        z = 1'b0;
        #10
        z = 1'b1;
        #10
        z = 1'b0;
        y = 1'b1;
        #10
        z = 1'b1;
        #10
        x = 1'b1;
        y = 1'b0;
        z = 1'b0;
        #10
        z = 1'b1;
        #10
        z = 1'b0;
        y = 1'b1;
        #10
        z = 1'b1;
    end
endmodule