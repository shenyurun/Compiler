struct Vector
{
float x, y;
};

struct Vector2
{
float fa, fb;
};

float dotMultiply(struct Vector v1, struct Vector v2)
{
return v1.x*v2.y-v1.y*v2.x;
}

int main()
{
float a[10], c[10], b[10], d[10];
int i = 0;
struct Vector sv1;
struct Vector2 sv2;
while(i<10)
{
sv1.x = a[i];
sv1.y = b[i];
sv2.fa = c[i];
sv2.fb = d[i];
i = i+1;

sv2 = sv1;
}
dotMultiply(sv1, sv2);
return 0;
}

