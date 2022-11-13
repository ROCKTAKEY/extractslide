#include <Siv3D.hpp> // OpenSiv3D v0.6.5

void Main(){
    // 背景の色を設定 | Set background color
    Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

    // 通常のフォントを作成 | Create a new font
    const Font font{ 60 };

    // 絵文字用フォントを作成 | Create a new emoji font
    const Font emojiFont{ 60, Typeface::ColorEmoji };

    // `font` が絵文字用フォントも使えるようにする | Set emojiFont as a fallback
    font.addFallback(emojiFont);

    VideoReader videoReader;

    String pendingFileName;

    while (System::Update()){
        // マウスカーソルに追随する半透明な円を描く | Draw a red transparent circle that follows the mouse cursor
        Circle{ Cursor::Pos(), 40 }.draw(ColorF{ 1, 0, 0, 0.5 });

        // もし [Button] が押されたら | When [Button] is pushed
        if (SimpleGUI::Button(U"Open video", Vec2{ 640, 40 })){
            auto fileInput = Dialog::OpenFile({FileFilter::AllVideoFiles()});
            if (fileInput.has_value()) {
                pendingFileName = fileInput.value();
            }
        }

        if (DragDrop::HasNewFilePaths()) {
            auto files = DragDrop::GetDroppedFilePaths();
            if (files.size() != 1) {
                Print << U"Do not drag and drop multiple files";
            } else {
                pendingFileName = files.front().path;
            }
        }

        if (pendingFileName) {
            PutText(pendingFileName, Arg::topLeft = Vector2D{100, 100});
        }
    }
}
