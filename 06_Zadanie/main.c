       #include <curses.h>
       #include <stdlib.h>
       #define CTRL(c) ((c) & 037)

       main (argc, argv)
       int argc;
       char **argv;
       {
         extern void perror(), exit();
         int i, n, l;
         int c;
         int line = 0;
         FILE *fd;

         if (argc != 2) {
           fprintf (stderr, "usage: %s file\n", argv [0]);
           exit (1);
         }

         fd = fopen (argv [1], "r");
         if (fd == NULL) {
           perror (argv [1]);
           exit (2);
         }

         initscr ();
         cbreak ();
         nonl ();
         noecho ();
         idlok (stdscr, TRUE);
         keypad (stdscr, TRUE);

         /* ������ ���� */
         while ((c = getc(fd)) != EOF) {
           if (c == '\n') line++;
           if (line > LINES - 2) break;
           addch(c);
         }
         fclose (fd);

         move (0, 0);
         refresh ();
         edit ();

         /* ���������� ���� */
         fd = fopen (argv [1], "w");
         for (l = 0; l < LINES - 1; l++) {
           n = len(l);
           for (i = 0; i < n; i++)
             putc (mvinch (l, i) & A_CHARTEXT, fd);
           putc('\n', fd);
         }
         fclose(fd);

         endwin ();
         exit (0);
       }

       len (lineno)
       int lineno;
       {
         int linelen = COLS - 1;

         while (linelen >= 0 && mvinch (lineno, linelen) == ' ')
           linelen--;
         return linelen + 1;
       }

       /* ���������� �������� �������� ��������� ������� */
       int row, col;

       edit ()
       {
         int c;

         for (;;) {
           move (row, col);
           refresh ();
           c = getch ();

           /* ������� ��������� */
           switch (c) {

             /* hjkl � �������: ���������� ������
                � ��������� ����������� */
             case 'h':
             case KEY_LEFT:
               if (col > 0) col--;
               else flash ();
               break;

             case 'j':
             case KEY_DOWN:
               if (row < LINES - 1) row++;
               else flash ();
               break;

             case 'k':
             case KEY_UP:
               if (row > 0) row--;
               else flash ();
               break;

             case 'l':
             case KEY_RIGHT:
               if (col < COLS - 1) col++;
               else flash ();
               break;

             /* i: ������� � ����� ����� */
             case KEY_IC:
             case 'i':
               input ();
               break;

             /* x: ������� ������� ������ */
             case KEY_DC:
             case 'x':
               delch ();
               break;

             /* o: �������� ������ � ������� � ����� ����� */
             case KEY_IL:
             case 'o':
               move (++row, col = 0);
               insertln ();
               input ();
               break;

             /* d: ������� ������� ������ */
             case KEY_DL:
             case 'd':
               deleteln ();
               break;

             /* CTRL+L: ������������ ����� */
             case KEY_CLEAR:
             case CTRL('L'):
               wrefresh (curscr);
               break;

             /* w: �������� � ��������� ������ */
             case 'w':
               return;

             /* q: ��������� ������ ��� ������ ����� */
             case 'q':
               endwin ();
               exit (2);

             default:
               flash ();
               break;
           }
         }
       }

       /* ����� �����: ��������� � ��������� �������
          �����: CTRL+D ��� EIC */
       input ()
       {
         int c;

         standout ();
         mvaddstr (LINES - 1, COLS - 20, "����� �����");
         standend ();
         move (row, col);
         refresh ();
           for (;;) {
             c = getch ();
             if (c == CTRL('D') || c == KEY_EIC) break;
             insch (c);
             move (row, ++col);
             refresh ();
           }
           move (LINES - 1, COLS - 20);
           clrtoeol ();
           move (row, col);
           refresh ();
       }
