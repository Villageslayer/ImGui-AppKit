// MenuWindow.cpp 
#include "../Global.h" 
void ShowExampleTable()
{
    // Begin a new table with 3 columns
    if (ImGui::BeginTable("ExampleTable", 3))
    {
        // Setup columns with headers
        ImGui::TableSetupColumn("Column 1");
        ImGui::TableSetupColumn("Column 2");
        ImGui::TableSetupColumn("Column 3");
        ImGui::TableHeadersRow();

        // Add rows and columns
        for (int row = 0; row < 5; ++row)
        {
            ImGui::TableNextRow();
            for (int column = 0; column < 3; ++column)
            {
                ImGui::TableSetColumnIndex(column);
                ImGui::Text("Row %d Column %d", row, column);
            }
        }

        // End the table
        ImGui::EndTable();
    }
}
void MenuWindow::Render() {
	Manager::SetNextSize(600, 400);
	Manager::SetNextFlags(flags);

	ShowExampleTable();
    

}
// MenuWindow.cpp