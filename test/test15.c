int product (int m1[4], int m2[4])
{
int sum = 0, i = 0;
while(i < 4)
{
sum = sum + m1[i] * m2[i];
i = i + 1;
}
return sum;
}
int main()
{
int m3[2][4], m4[4][2], p[2][2], temp1[4], temp2[4];
int j = 0, k = 0, l = 0;
while(j < 2)
{
while(k < 4)
{
m3[j][k] = j + 1;
m4[k][j] = k + 1;
k = k + 1;
}
k = 0;
j = j + 1;
}
j = k = 0;
while(j < 2)
{
while(l < 4)
{
temp1[l] = m3[j][l];
l = l + 1;
}
l = 0;
while(k < 2)
{
while(l < 4)
{
temp2[l] = m4[l][k];
l = l + 1;
}
l = 0;
p[j][k] = product(temp1, temp2);
write(p[j][k]);
k = k + 1;
}
k = 0;
j = j + 1;
}
return 0;
}

