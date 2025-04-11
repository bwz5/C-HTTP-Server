/*
    FOUND FROM: https://www.reddit.com/r/C_Programming/comments/11at6d8/generate_html_in_c/
*/

#ifndef HTML_TAGS_H_
#define HTML_TAGS_H_

#define SCOPE(atStart, atEnd) for (int _scope_break = ((atStart), 1); _scope_break; _scope_break = ((atEnd), 0))

#define DOCTYPE fputs("<!DOCTYPE html>", fp)
#define HTML(lang) SCOPE(fprintf(fp, "<html lang='%s'>", lang), fputs("</html>", fp))
#define HEAD() SCOPE(fputs("<head>", fp), fputs("</head>",fp))
#define TITLE(text) fprintf(fp, "<title>%s</title>", text)
#define META(attributes) fprintf(fp, "<meta %s>", attributes)
#define LINK(attributes) fprintf(fp, "<link %s>", attributes)
#define SCRIPT(src) fprintf(fp, "<script src='%s'></script>", src)
#define BODY(attributes) SCOPE(fprintf(fp, "<body %s>", attributes), fputs("</body>", fp))
#define DIV(attributes) SCOPE(fprintf(fp, "<div %s>", attributes), fputs("</div>", fp))
#define UL(attributes) SCOPE(fprintf(fp, "<ul %s>", attributes), fputs("</ul>", fp))
#define OL(attributes) SCOPE(fprintf(fp, "<ol %s>", attributes), fputs("</ol>", fp))
#define LI(attributes) SCOPE(fprintf(fp, "<li %s>", attributes), fputs("</li>", fp))
#define BR fputs("<br>", fp)
#define _(...) fprintf(fp, __VA_ARGS__)
#define H1(attributes) SCOPE(fprintf(fp, "<h1 %s>", attributes), fputs("</h1>", fp))
#define H2(attributes) SCOPE(fprintf(fp, "<h2 %s>", attributes), fputs("</h2>", fp))
#define H3(attributes) SCOPE(fprintf(fp, "<h3 %s>", attributes), fputs("</h3>", fp))
#define H4(attributes) SCOPE(fprintf(fp, "<h4 %s>", attributes), fputs("</h4>", fp))
#define H5(attributes) SCOPE(fprintf(fp, "<h5 %s>", attributes), fputs("</h5>", fp))
#define H6(attributes) SCOPE(fprintf(fp, "<h6 %s>", attributes), fputs("</h6>", fp))
#define P(content) fprintf(fp, "<p>%s</p>", content)
#define A(href, content) fprintf(fp, "<a href='%s'>%s</a>", href, content)
#define IMG(attributes) fprintf(fp, "<img %s>", attributes)
#define HR fputs("<hr/>", fp)
#define TABLE(attributes) SCOPE(fprintf(fp, "<table %s>", attributes), fputs("</table>", fp)
#define TR(attributes) SCOPE(fprintf(fp, "<tr %s>", attributes), fputs("</tr>", fp))
#define TD(attributes) SCOPE(fprintf(fp, "<td %s>", attributes), fputs("</td>", fp))
#define TH(attributes) SCOPE(fprintf(fp, "<th %s>", attributes), fputs("</th>", fp))
#define FORM(attributes) SCOPE(fprintf(fp, "<form %s>", attributes), fputs("</form>", fp))
#define INPUT(attributes) fprintf(fp, "<input %s>", attributes)
#define OPTION(attributes, content) fprintf(fp, "<option %s>%s</option>", attributes, content)

#endif