void editorDrawRows()
{
  int y;
  for (y = 0; y < E.screenRows; y++)
  {
    write(STDOUT_FILENO, "~\r\n", 3);
  }
}