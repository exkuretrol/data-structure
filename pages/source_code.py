import streamlit as st

from menu import menu_with_redirect, subject_options

menu_with_redirect()

st.header("程式碼說明")

hw_names = {
    "hw1": "作業一",
    "hw2": "作業二",
    "hw3": "作業三",
    "hw3.5": "加分作業",
    "hw4": "作業四",
    "hw5": "作業五",
    "hw6": "作業六",
}


subject = st.selectbox(
    label="課程",
    options=subject_options,
    format_func=lambda x: subject_options.get(x),
    index=1,
)
hw = st.selectbox(label="作業", options=hw_names, format_func=lambda x: hw_names.get(x))

if subject == "data_structure":
    if hw == "hw2":
        tab0, tab1, tab2, tab3, tab4 = st.tabs(
            [
                "main.cpp",
                "permutation.hpp",
                "tower-of-honai.hpp",
                "Permutation.py",
                "Tower_of_Honai.py",
            ]
        )

        with tab0:
            with open("src/main.cpp") as f:
                src = f.read()
            st.code(src, language="cpp")

        with tab1:
            with open("src/permutation.hpp") as f:
                src = f.read()
            st.code(src, language="cpp")

        with tab2:
            with open("src/tower-of-honai.hpp") as f:
                src = f.read()
            st.code(src, language="cpp")

        with tab3:
            with open("pages/HW02_Permutation.py") as f:
                src = f.read()
            st.code(src)

        with tab4:
            with open("pages/HW02_Tower_of_Honai.py") as f:
                src = f.read()
            st.code(src)
    elif hw == "hw3":
        tab0, tab1, tab2 = st.tabs(["main.cpp", "magic-square.hpp", "Magic_Square.py"])
        with tab0:
            with open("src/main.cpp") as f:
                src = f.read()
            st.code(src, language="cpp")

        with tab1:
            with open("src/magic-square.hpp") as f:
                src = f.read()
            st.code(src, language="cpp")

        with tab2:
            with open("pages/HW03_Magic_Square.py") as f:
                src = f.read()
            st.code(src)
    elif hw == "hw3.5":
        tab0, tab1, tab2 = st.tabs(["main.cpp", "knights-tour.hpp", "Knight's_Tour.py"])
        with tab0:
            with open("src/main.cpp") as f:
                src = f.read()
            st.code(src, language="cpp")

        with tab1:
            with open("src/knights-tour.hpp") as f:
                src = f.read()
            st.code(src, language="cpp")

        with tab2:
            with open("pages/HW03a_Knight's_Tour.py") as f:
                src = f.read()
            st.code(src)

    if hw == "hw6":
        tab0, tab1, tab2, tab3, tab4, tab5, tab6 = st.tabs(
            [
                "main.cpp",
                "singly-circular-linked-list.hpp",
                "doubly-circular-linked-list.hpp",
                "linked-stack.hpp",
                "Singly_Circular_Linked_List.py",
                "Doubly_Circular_Linked_List.py",
                "Linked_Stack.py",
            ]
        )

        with tab0:
            with open("src/main.cpp") as f:
                src = f.read()
            st.code(src, language="cpp")

        with tab1:
            with open("src/singly-circular-linked-list.hpp") as f:
                src = f.read()
            st.code(src, language="cpp")

        with tab2:
            with open("src/doubly-circular-linked-list.hpp") as f:
                src = f.read()
            st.code(src, language="cpp")

        with tab3:
            with open("src/linked-stack.hpp") as f:
                src = f.read()
            st.code(src, language="cpp")

        with tab4:
            with open("pages/HW06a_Singly_Circular_Linked_List.py") as f:
                src = f.read()
            st.code(src)

        with tab5:
            with open("pages/HW06b_Doubly_Circular_Linked_List.py") as f:
                src = f.read()
            st.code(src)

        with tab6:
            with open("pages/HW06c_Linked_Stack.py") as f:
                src = f.read()
            st.code(src)
    else:
        st.write("還沒寫完")
else:
    if hw == "hw1":
        tab0, tab1, tab2 = st.tabs(
            ["main.cpp", "binary-search-tree.hpp", "Binary_Search_Tree.py"]
        )
        with tab0:
            with open("src/main.cpp") as f:
                src = f.read()
            st.code(src, language="cpp")

        with tab1:
            with open("src/binary-search-tree.hpp") as f:
                src = f.read()
            st.code(src, language="cpp")

        with tab2:
            with open("pages/HW01_Binary_Search_Tree.py") as f:
                src = f.read()
            st.code(src)
    elif hw == "hw2":
        tab0, tab1, tab2 = st.tabs(
            ["main.cpp", "binary-search-tree.hpp", "Binary_Search_Tree_Iteration.py"]
        )
        with tab0:
            with open("src/main.cpp") as f:
                src = f.read()
            st.code(src, language="cpp")

        with tab1:
            with open("src/binary-search-tree.hpp") as f:
                src = f.read()
            st.code(src, language="cpp")

        with tab2:
            with open("pages/HW02_Binary_Search_Tree_Iteration.py") as f:
                src = f.read()
            st.code(src)
    elif hw == "hw3":
        tab0, tab1, tab2 = st.tabs(
            ["main.cpp", "binary-search-tree.hpp", "Binary_Search_Tree_Iteration.py"]
        )
        with tab0:
            with open("src/main.cpp") as f:
                src = f.read()
            st.code(src, language="cpp")

        with tab1:
            with open("src/binary-search-tree.hpp") as f:
                src = f.read()
            st.code(src, language="cpp")

        with tab2:
            with open("pages/HW03_Binary_Search_Tree_Construct_Unique_Tree.py") as f:
                src = f.read()
            st.code(src)
    else:
        st.write("還沒寫完")
