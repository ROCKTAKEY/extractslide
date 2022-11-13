# LinuxにおけるOpenSiv3Dプロジェクトのテンプレート
このレポジトリは、[OpenSiv3D](https://siv3d.github.io/)を利用したプログラムを、
Linuxでそのままビルドできるようにしておくためのテンプレートプロジェクトです。

- Siv3D: v0.6.5

## 使い方
### GitHubレポジトリの作成
1. 「Use this template」を押下
2. 「Repository name」と「Descipion」(任意)を入力
3. 「Public」「Private」を選択
4. 「Create repository from template」を押下

### Linuxでビルドする
1. 自分のプロジェクトをクローン(`<username>`と`<your-project>`は適宜自分のものに変えてください)
```shell
git clone https://github.com/<username>/<your-project>
```
2. [公式サイト](https://siv3d.github.io/download/ubuntu/)を参考にSiv3D本体をビルド、インストール
3. エンジン([`Linux/App/resources/engine/`](https://github.com/Siv3D/OpenSiv3D/tree/main/Linux/App/resources/))をこのプロジェクトにコピーする
   1. OpenSiv3Dをクローン
   ```shell
   git clone https://github.com/Siv3D/OpenSiv3D /tmp/OpenSiv3D --depth=1
   ```
   2. エンジンをコピー(`/path/to/project/`は適宜自分のプロジェクトのクローン場所に変更)
   ```shell
   cd /path/to/project/
   mkdir resources
   cp -r /tmp/OpenSiv3D/Linux/App/resources/engine ./resources/engine
   ```
4. 自分のプロジェクトをビルドする
   1. プロジェクトのディレクトリに移る
   ```shell
   cd /path/to/project/
   ```
   2. ビルドの準備をする(`ninja`でなく`make`を使うのであれば`-GNinja`は不要)
   ```shell
   mkdir build && cd build
   cmake -GNinja -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
   ```
   3. ビルドする
   ```shell
   cmake --build build
   ```
5. 実行する(実行ファイル名は最初に変更した通りに変更)
```shell
./Siv3DExampleProject
```

## CMakeLists.txtの書き換え
この項は必ずしも行う必要はないですが、公開するときにプロジェクトや実行ファイルの名前が独自のもののほうがかっこいいです。
また、複数ファイルにまたがる大きなプロジェクトとなるときには、対象を追加するために必要になります。

### プロジェクト名の変更
- [CMakeLists.txt](CMakeLists.txt)の2行目の`OpenSiv3D_Linux_App`という語を任意の名前に変更する。

### 実行ファイルの名前の変更
- [CMakeLists.txt](CMakeLists.txt)の全ての`Siv3DExampleProject`という単語を任意の名前に置換する。

### cppファイルの追加
- [CMakeLists.txt](CMakeLists.txt)の`# Add cpp files here`以降にcppファイルを追加する

## トラブルシューティング
### エディタや言語サーバーがSiv3Dをみつけられず、エラーを大量に表示してしまう
`build`ディレクトリで、以下のコードを実行してください
```shell
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .. && cp compile_commands.json ../
```
これにより、ルートディレクトリに`compile_commands.json`が生成されます。
このファイルはコンパイルに必要な情報を全て含むため、ライブラリやヘッダファイルの場所を
エディタや言語サーバーに知らせることができます。
