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

         /* Читаем файл */
         while ((c = getc(fd)) != EOF) {
           if (c == '\n') line++;
           if (line > LINES - 2) break;
           addch(c);
         }
         fclose (fd);

         move (0, 0);
         refresh ();
         edit ();

         /* Записываем файл */
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

       /* Глобальное значение текущего положения курсора */
       int row, col;

       edit ()
       {
         int c;

         for (;;) {
           move (row, col);
           refresh ();
           c = getch ();

           /* Команды редактора */
           switch (c) {

             /* hjkl и стрелки: перемещают курсор
                в указанном направлении */
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

             /* i: переход в режим ввода */
             case KEY_IC:
             case 'i':
               input ();
               break;

             /* x: удалить текущий символ */
             case KEY_DC:
             case 'x':
               delch ();
               break;

             /* o: вставить строку и перейти в режим ввода */
             case KEY_IL:
             case 'o':
               move (++row, col = 0);
               insertln ();
               input ();
               break;

             /* d: удалить текущую строку */
             case KEY_DL:
             case 'd':
               deleteln ();
               break;

             /* CTRL+L: перерисовать экран */
             case KEY_CLEAR:
             case CTRL('L'):
               wrefresh (curscr);
               break;

             /* w: записать и закончить работу */
             case 'w':
               return;

             /* q: закончить работу без записи файла */
             case 'q':
               endwin ();
               exit (2);

             default:
               flash ();
               break;
           }
         }
       }

       /* Режим ввода: принимает и вставляет символы
          Выход: CTRL+D или EIC */
       input ()
       {
         int c;

         standout ();
         mvaddstr (LINES - 1, COLS - 20, "Режим ввода");
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
