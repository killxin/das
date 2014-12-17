#ifndef _BLOG_
#define _BLOG_

_Bool Deal_Friend (Graph* pg, int start, int end);
_Bool Deal_At (Graph* pg, int start, int end);
_Bool Set_circle(Graph* pg, Circle* pc);
_Bool Judge_Friend (Circle* pc, int user1, int user2);
int Get_Frequency (Graph* pg, Circle* pc, int user1, int user2);
int Common_Friend (Circle* pc, int user1, user2);

#endif
