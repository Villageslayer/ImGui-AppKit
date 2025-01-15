#define BUTTON ImGui::Button
#define ABUTTON ImGui::ArrowButton
#define CHECKBOX ImGui::Checkbox
#define INPUTTEXT ImGui::InputText

#define SAMELINE ImGui::SameLine();
#define SPACING ImGui::Spacing();
#define SEPARATOR ImGui::Separator();
#define TXT ImGui::Text

#define SETCURSORPOS ImGui::SetCursorPosX
#define GETCURSORPOS ImGui::GetCursorPosX

#define ISIZE(w,h) ImVec2((w) ? (w) : 0, (h) ? (h) : 0)
#define IV2(x,y) ImVec2(x,y)
#define IV3(x,y,z) ImVec3(x,y,z)
#define IV4(x,y,z,w) ImVec4(x,y,z,w)


#define DUMMY(w,h) ImGui::Dummy(ISIZE(w,h));

#define BCHILD ImGui::BeginChild
#define ABCHILD(x,ISIZE,f) ImGui::BeginChild(x,ISIZE,(f)?(f):0);
#define ENDCHILD ImGui::EndChild();
#define CHILD(x, size, y,f) ABCHILD(x, size,f); y; ENDCHILD;




#define COlUMNS ImGui::Columns
#define NEXTCOLUMN ImGui::NextColumn();


// COLORS

#define COLOR_WHITE      ImVec4(1.0f, 1.0f, 1.0f, 1.0f)
#define COLOR_BLACK      ImVec4(0.0f, 0.0f, 0.0f, 1.0f)
#define COLOR_RED        ImVec4(1.0f, 0.0f, 0.0f, 1.0f)
#define COLOR_GREEN      ImVec4(0.0f, 1.0f, 0.0f, 1.0f)
#define COLOR_BLUE       ImVec4(0.0f, 0.0f, 1.0f, 1.0f)
#define COLOR_YELLOW     ImVec4(1.0f, 1.0f, 0.0f, 1.0f)
#define COLOR_CYAN       ImVec4(0.0f, 1.0f, 1.0f, 1.0f)
#define COLOR_MAGENTA    ImVec4(1.0f, 0.0f, 1.0f, 1.0f)
#define COLOR_ORANGE    ImVec4(1.0f, 0.65f, 0.0f, 1.0f)
#define COLOR_TRANSPARENT ImVec4(0.0f, 0.0f, 0.0f, 0.0f)


// FLAGS
// ImGui Window Flags
#define NONE 0
#define NTITLEBAR (1 << 0)
#define NRESIZE (1 << 1)
#define NMOVE (1 << 2)
#define NSCROLLBAR (1 << 3)
#define NSCROLLWITHMOUSE (1 << 4)
#define NCOLLAPSE (1 << 5)
#define ALWAYSAUTORESIZE (1 << 6)
#define NBACKGROUND (1 << 7)
#define NSAVEDSETTINGS (1 << 8)
#define NMOUSEINPUTS (1 << 9)
#define MENUBAR (1 << 10)
#define HORIZONTALSROLLBAR (1 << 11)
#define NFOCUSONAPPEARING (1 << 12)
#define NBRINGTOFRONTONFOCUS (1 << 13)
#define ALWAYSVERTICALSCROLLBAR (1 << 14)
#define ALWAYSHORIZONTALSCROLLBAR (1 << 15)
#define ALWAYSUSEWINDOWPADDING (1 << 16)
#define NNAVINPUTS (1 << 18)
#define NNAVFOCUS (1 << 19)
#define UNSAVEDDOCUMENT (1 << 20)
#define NDOCKING (1 << 21)
#define NNAV (NNAVINPUTS | NNAVFOCUS)
#define NDECORATION (NTITLEBAR | NRESIZE | NSCROLLBAR | NCOLLAPSE)
#define NINPUTS (NMOUSEINPUTS | NNAVINPUTS | NNAVFOCUS)

// ImGui Child Window Flags
#define CNONE 0
#define CNMOVE (1 << 0)
#define CALWAYSUSEWINDOWPADDING (1 << 1)
#define BORDER 1


