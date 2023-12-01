module fullAdder(x, y, cin, cout, sum);
    input x, y, cin;
    output cout, sum;
    xor(xor_x_y, x, y);
    xor(sum, xor_x_y, cin);
    and(cin_and_xor_x_y, cin, xor_x_y);
    and(and_x_y, x, y);
    or(cout, cin_and_xor_x_y, and_x_y);
endmodule

module test_fullAdder();
    reg x, y, cin;
    wire cout, sum;
    fullAdder test(.x(x), .y(y), .cin(cin), .cout(cout), .sum(sum));
    initial begin
        x = 1'b0;
        y = 1'b0;
        cin = 1'b0;
        #10
        cin = 1'b1;
        #10
        cin = 1'b0;
        y = 1'b1;
        #10
        cin = 1'b1;
        #10
        x = 1'b1;
        y = 1'b0;
        cin = 1'b0;
        #10
        cin = 1'b1;
        #10
        cin = 1'b0;
        y = 1'b1;
        #10
        cin = 1'b1;
    end
endmodule