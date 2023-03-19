#include <ctype.h>
#include <curses.h>

int d, i, j, m, n, p, q, x, y;

char k[] = "hjklHJKL[]tbixWRQ";
char b[BUF], *g = b;
char *c, *f, *h, *t;

char *
Z(int a)
{
	if (a < 0)
		return b;
	return b + a + (b + a < g ? 0 : h - g);
}

int
P(char *a)
{
	return a - b - (a < h ? 0 : h - g);
}

int
S()
{
	p = 0;
}

int
bf()
{
	n = p = P(c);
}

int
Q()
{
	q = 1;
}

int
C()
{
	clear();
	Y();
}

int
G()
{
	t = Z(p);
	while (t < g)
		*--h = *--g;
	while (h < t)
		*g++ = *h++;
	p = P(h);
}

int
B()
{
	while (!isspace(*(t = Z(p))) && b < t)
		--p;
	while (isspace(*(t = Z(p))) && b < t)
		--p;
}

int
M(int a)
{
	while (b < (t = Z(--a)) && *t - '\n')
		;
	return b < t ? ++a : 0;
}

int
N(int a)
{
	while ((t = Z(a++)) < c && *t - '\n')
		;
	return t < c ? a : P(c);
}

int
A(int a, int j)
{
	i = 0;
	while ((t = Z(a)) < c && *t - '\n' && i < j) {
		i += *t - '\t' ? 1 : 8 - (i & 7);
		++a;
	}
	return a;
}

int
L()
{
	0 < p && --p;
}

int
R()
{
	p < P(c) && ++p;
}

int
U()
{
	p = A(M(M(p) - 1), x);
}

int
D()
{
	p = A(N(p), x);
}

int
H()
{
	p = M(p);
}

int
E()
{
	p = N(p);
	L();
}

int
J()
{
	m = p = M(n - 1);
	while (0 < y--)
		D();
	n = P(c);
}

int
K()
{
	j = d;
	while (0 < --j)
		m = M(m - 1), U();
}

int
I()
{
	G();
	while ((j = getch()) - '\f') {
		if (j - '\b')
			g - h && (*g++ = j - '\r' ? j : '\n');
		else
			b < g && --g;
		p = P(h);
		Y();
	}
}

int
X()
{
	G();
	p = h < c ? P(++h) : p;
}

int
F()
{
	j = p;
	p = 0;
	G();
	write(i = creat(f, MODE), h, (int)(c - h));
	close(i);
	p = j;
}

int
W()
{
	while (!isspace(*(t = Z(p))) && t < c)
		++p;
	while (isspace(*(t = Z(p))) && t < c)
		++p;
}

int (*z[])() = { L, D, U, R, B, J, K, W, H, E, S, bf, I, X, F, C, Q, G };

int
Y()
{
	m = p < m ? M(p) : m;
	if (n <= p) {
		m = N(p);
		i = m - P(c) ? d : d - 2;
		while (0 < i--)
			m = M(m - 1);
	}
	move(0, 0);
	i = j = 0;
	n = m;
	while (1) {
		p - n || (y = i, x = j);
		t = Z(n);
		if (d <= i || c <= t)
			break;
		if (*t - '\r')
			addch(*t), j += *t - '\t' ? 1 : 8 - (j & 7);
		if (*t == '\n' || COLS <= j)
			++i, j = 0;
		++n;
	}
	clrtobot();
	++i < d&& mvaddstr(i, 0, "<< EOF >>");
	move(y, x);
	refresh();
}

int
main(int argc, char **argv)
{
	h = c = b + BUF;
	if (argc < 2)
		return 2;
	initscr();
	d = LINES;
	raw();
	noecho();
	idlok(stdscr, 1);
	if (0 < (i = open(f = *++argv, 0))) {
		g += read(i, b, BUF);
		g = g < b ? b : g;
		close(i);
	}
	S();
	while (!q) {
		Y();
		i = 0;
		j = getch();
		while (k[i] && j - k[i])
			++i;
		(*z[i])();
	}
	endwin();
	return 0;
}

