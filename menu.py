import streamlit as st


def construct_page_path(page_name: str) -> str:
    pages_dir = "pages"
    path = [pages_dir]
    path.append(page_name)

    return "/".join(path)


def data_structure_menu():
    st.session_state.page_category = "data_structure"
    st.sidebar.page_link(
        page=construct_page_path("HW02_Permutation.py"),
        label="HW 02 排列",
        icon="🌧️",
    )

    st.sidebar.page_link(
        page=construct_page_path("HW02_Tower_of_Honai.py"),
        label="HW 02 河內塔",
        icon="️🗼",
    )

    st.sidebar.page_link(
        page=construct_page_path("HW03_Magic_Square.py"),
        label="HW 03 魔術方陣",
        icon="⏹️",
    )

    st.sidebar.page_link(
        page=construct_page_path("HW03a_Knight's_Tour.py"),
        label="HW 03a 騎士巡迴",
        icon="♟️",
    )

    st.sidebar.page_link(
        page=construct_page_path("HW06a_Singly_Circular_Linked_List.py"),
        label="HW 06a 單向循環鏈結串列",
        icon="➡️",
    )

    st.sidebar.page_link(
        page=construct_page_path("HW06b_Doubly_Circular_Linked_List.py"),
        label="HW 06b 雙向循環鏈結串列",
        icon="↔️",
    )

    st.sidebar.page_link(
        page=construct_page_path("HW06c_Linked_Stack.py"),
        label="HW 06c 鏈結堆疊",
        icon="📚",
    )


def algorithm_menu():
    st.session_state.page_category = "algorithm"
    st.sidebar.page_link(
        page=construct_page_path("HW01_Binary_Search_Tree.py"),
        label="HW 01 二元搜尋樹（遞迴）",
        icon="🎄",
    )
    st.sidebar.page_link(
        page=construct_page_path("HW02_Binary_Search_Tree_Iteration.py"),
        label="HW 02 二元搜尋樹（遞迴 / 迭代）",
        icon="🎄",
    )


subject_options = {"data_structure": "資料結構", "algorithm": "演算法"}


def menu():

    st.sidebar.page_link(page="app.py", label="首頁", icon="🏠")

    def set_subject():
        st.session_state.subject = st.session_state._subject

    subject = st.sidebar.selectbox(
        label="課程",
        options=subject_options,
        format_func=lambda x: subject_options.get(x),
        index=(
            list(subject_options.keys()).index(st.session_state._subject)
            if "_subject" in st.session_state
            else 1
        ),
        on_change=set_subject,
        key="_subject",
    )
    if subject == "data_structure":
        data_structure_menu()
    else:
        algorithm_menu()


def menu_with_redirect():

    # if "subject" not in st.session_state or st.session_state is None:
    #     st.switch_page(page="app.py")
    menu()
