#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <curses.h>

int height;				/* Height of screen in lines. */

char buffer[BUF];		/* Main buffer. */
char *bufptr = buffer;	/* Buffer location pointer. */

char *filename;			/* File name. */
int fd;					/* File descriptor. */

int j, m, n, p, q, x, y;

char k[] = "hjklHJKL[]tbixWRQ";
char *c, *h, *t;

char *
Z(int a)
{
	if (a < 0)
		return buffer;
	return buffer + a + (buffer + a < bufptr ? 0 : h - bufptr);
}

int
P(char *a)
{
	return a - buffer - (a < h ? 0 : h - bufptr);
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
	while (t < bufptr)
		*--h = *--bufptr;
	while (h < t)
		*bufptr++ = *h++;
	p = P(h);
}

int
B()
{
	while (!isspace(*(t = Z(p))) && buffer < t)
		--p;
	while (isspace(*(t = Z(p))) && buffer < t)
		--p;
}

int
M(int a)
{
	while (buffer < (t = Z(--a)) && *t - '\n')
		;
	return buffer < t ? ++a : 0;
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
	fd = 0;
	while ((t = Z(a)) < c && *t - '\n' && fd < j) {
		fd += *t - '\t' ? 1 : 8 - (fd & 7);
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
	j = height;
	while (0 < --j)
		m = M(m - 1), U();
}

int
I()
{
	G();
	while ((j = getch()) - '\f') {
		if (j - '\b')
			bufptr - h && (*bufptr++ = j - '\r' ? j : '\n');
		else
			buffer < bufptr && --bufptr;
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
	write(fd = creat(filename, MODE), h, (int)(c - h));
	close(fd);
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
		fd = m - P(c) ? height : height - 2;
		while (0 < fd--)
			m = M(m - 1);
	}
	move(0, 0);
	fd = j = 0;
	n = m;
	while (1) {
		p - n || (y = fd, x = j);
		t = Z(n);
		if (height <= fd || c <= t)
			break;
		if (*t - '\r')
			addch(*t), j += *t - '\t' ? 1 : 8 - (j & 7);
		if (*t == '\n' || COLS <= j)
			++fd, j = 0;
		++n;
	}
	clrtobot();
	++fd < height && mvaddstr(fd, 0, "<< EOF >>");
	move(y, x);
	refresh();
}

int
main(int argc, char **argv)
{
	h = c = buffer + BUF;

	if (argc < 2)
		return 2;

	initscr();

	height = LINES;

	raw();
	noecho();
	idlok(stdscr, 1);

	if ((fd = open(filename = *++argv, 0)) > 0) {
		if ((bufptr += read(fd, buffer, BUF)) <= 0)
			bufptr = buffer;
		
		close(fd);
	}

	//S();
	p = 0;

	while (!q) {
		Y();

		fd = 0;

		j = getch();
		while (k[fd] && j - k[fd])
			++fd;
		
		(*z[fd])();
	}

	endwin();
	return 0;
}

