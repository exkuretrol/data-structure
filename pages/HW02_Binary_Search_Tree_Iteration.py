import random

import streamlit as st
from homework import BinarySearchTreeInt

import redirect as rd
from menu import menu_with_redirect

menu_with_redirect()
st.header("二元搜尋樹")
st.caption("Binary Search Tree")

c0 = st.empty()
c1 = st.container(border=True)
c2 = st.container(border=True)

mode_options = {"recursion": "遞迴", "iteration": "迭代"}
mode = c0.selectbox(
    "mode",
    options=mode_options,
    format_func=lambda x: f"{mode_options.get(x)} {x}",
    index=1,
)

if "toggled" not in st.session_state:
    st.session_state.toggled = False


with c1:
    col1, col2 = st.columns([1, 1])
    with col1:
        input_options_action = {"create": "新增", "search": "搜尋", "delete": "刪除"}

        input_action = st.radio(
            "action",
            input_options_action,
            format_func=lambda x: input_options_action.get(x),
            horizontal=True,
        )
    with col2:
        output_options_action = {
            "preorder": "前序",
            "inorder": "中序",
            "postorder": "後序",
            "levelorder": "階層",
        }

        output_action = st.radio(
            "output",
            output_options_action,
            format_func=lambda x: output_options_action.get(x),
            horizontal=True,
            index=1,
        )


with c2:
    if input_action == "create":
        input_options_method = {"manual": "手動設定", "random": "隨機產生"}

        input_method = st.radio(
            "method",
            input_options_method,
            format_func=lambda x: input_options_method.get(x),
            index=1,
            horizontal=True,
        )

        if input_method == "manual":
            input_num = st.number_input("num", min_value=0, max_value=2**31 - 1)

            st.sidebar.markdown(
                """
            `num`：輸入二元樹的數字。
            """
            )

        else:
            col1, col2 = st.columns([1, 3], gap="medium")
            with col1:
                input_n = st.number_input("n", min_value=1, max_value=100, value=3)
            with col2:
                input_minmax = st.slider(
                    "minmax",
                    min_value=0,
                    max_value=1000,
                    value=(0, 100),
                )
            st.sidebar.markdown(
                """
            `n`：隨機輸入二元樹 n 個數字。

            `minmax`：輸入二元樹的數字的最大最小值。
            """
            )
    else:
        input_target = st.number_input("target", min_value=0, max_value=2**31 - 1)
    col1, col2, _ = st.columns([2, 2, 9])
    with col1:
        btn_action = st.button(
            input_options_action.get(input_action),
            type="primary",
            use_container_width=True,
        )

    with col2:
        btn_empty = st.button(
            ":violet[清空 :bomb:]", type="secondary", use_container_width=True
        )


@st.cache_resource
def init_bst():
    return BinarySearchTreeInt()


bst = init_bst()


def insert(num: int):
    if mode == "recursion":
        bst.insert(num)
    else:
        bst.insert_iter(num)
    st.toast(f"已新增 {num} 到二元樹中 ({mode_options.get(mode)})")


def search(num: int):
    if mode == "recursion":
        result = bst.search(num)
    else:
        result = bst.search_iter(num)

    if result:
        st.info(f"{num} 找到ㄌ ({mode_options.get(mode)})")
    else:
        st.error(f"找不到 {num}! ({mode_options.get(mode)})")
        col1, col2, _ = st.columns([2, 2, 10])
        col1.button(
            f"新增 {num}",
            on_click=insert,
            kwargs={"num": num},
            type="primary",
            use_container_width=True,
        )
        col2.button("忽略", use_container_width=True)


def delete(num: int):
    # quick fix, I'm tired :p
    if mode == "recursion":
        result = bst.search(num)
        if result:
            bst.delete(num)
            st.info(f"刪除了數字 {num} ({mode_options.get(mode)})")
        else:
            st.error(f"找不到 {num}! ({mode_options.get(mode)})")
            col1, col2, _ = st.columns([2, 2, 10])
            col1.button(
                f"新增 {num}",
                on_click=insert,
                kwargs={"num": num},
                type="primary",
                use_container_width=True,
            )
            col2.button("忽略", use_container_width=True)
    else:
        result = bst.delete_iter(num)
        if result == -1:
            st.error(f"找不到 {num}! ({mode_options.get(mode)})")
            col1, col2, _ = st.columns([2, 2, 10])
            col1.button(
                f"新增 {num}",
                on_click=insert,
                kwargs={"num": num},
                type="primary",
                use_container_width=True,
            )
            col2.button("忽略", use_container_width=True)
        else:
            st.info(f"刪除了數字 {num} ({mode_options.get(mode)})")


def empty():
    bst.empty()


if btn_action:
    st.session_state.toggled = True
    if input_action == "create":
        if input_method == "manual":
            insert(input_num)
        else:
            m, M = input_minmax
            for _ in range(input_n):
                num = random.randint(m, M)
                insert(num)
    elif input_action == "search":
        search(input_target)
    elif input_action == "delete":
        delete(input_target)

if btn_empty:
    empty()


code = st.code(language="css", body="", line_numbers=True)

if st.session_state.toggled:
    with rd.stdout(to=code):
        if output_action == "preorder":
            bst.print(0, mode == "iteration")
        elif output_action == "inorder":
            bst.print(1, mode == "iteration")
        elif output_action == "postorder":
            bst.print(2, mode == "iteration")
        else:
            bst.print(3, mode == "iteration")
