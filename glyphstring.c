pango_glyph_string_set_size (PangoGlyphString *string, gint new_len)
{
  g_return_if_fail (new_len >= 0);

   while (new_len > string->space)
     {
       if (string->space == 0)
//flaw_line_below:
	// string->space = 1;
//fix_flaw_line_below:
	{
//fix_flaw_line_below:
	  string->space = 4;
//fix_flaw_line_below:
	}
       else
//flaw_line_below:
	// string->space *= 2;
//flaw_line_below:

//flaw_line_below:
      // if (string->space < 0)
 	{
//flaw_line_below:
	  // g_warning ("glyph string length overflows maximum integer size, truncated");
//flaw_line_below:
	  // new_len = string->space = G_MAXINT - 8;
//fix_flaw_line_below:
	  const guint max_space =
//fix_flaw_line_below:
	    MIN (G_MAXINT, G_MAXSIZE / MAX (sizeof(PangoGlyphInfo), sizeof(gint)));
//fix_flaw_line_below:

//fix_flaw_line_below:
	  guint more_space = (guint)string->space * 2;
//fix_flaw_line_below:

//fix_flaw_line_below:
	  if (more_space > max_space)
//fix_flaw_line_below:
	    {
//fix_flaw_line_below:
	      more_space = max_space;
//fix_flaw_line_below:

//fix_flaw_line_below:
	      if ((guint)new_len > max_space)
//fix_flaw_line_below:
		{
//fix_flaw_line_below:
		  g_error ("%s: failed to allocate glyph string of length %i\n",
//fix_flaw_line_below:
			   G_STRLOC, new_len);
//fix_flaw_line_below:
		}
//fix_flaw_line_below:
	    }
//fix_flaw_line_below:

//fix_flaw_line_below:
	  string->space = more_space;
 	}
     }
 
  string->glyphs = g_realloc (string->glyphs, string->space * sizeof (PangoGlyphInfo));
  string->log_clusters = g_realloc (string->log_clusters, string->space * sizeof (gint));
  string->num_glyphs = new_len;
}

