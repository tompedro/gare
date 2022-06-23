{ NOTE: it is recommended to use this even if you don't understand the following code. }

{ constraints }
const
    MAXN = 50000;

{ input data }
var
    N, T, i  : longint;
    hashtags : array[0..MAXN-1] of string;

begin
{
    uncomment the following lines if you want to read/write from files
    assign(input,  'input.txt');  reset(input);
    assign(output, 'output.txt'); rewrite(output);
}

    readln(N, T);
    for i:=0 to N-1 do
        read(hashtags[i]);
    readln();

    { insert your code here }

    writeln(hashtags[0]); { print result }
end.
