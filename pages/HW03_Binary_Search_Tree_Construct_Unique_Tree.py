import random
import re
import string

import streamlit as st
from homework import BinarySearchTreeChar, BinarySearchTreeInt

import redirect as rd
from menu import menu_with_redirect

menu_with_redirect()
st.header("二元搜尋樹")
st.caption("Binary Search Tree")

c0 = st.container(border=False)
c1 = st.container(border=True)
c2 = st.container(border=True)

sidebar_text_list = list()
sidebar_text_list.append("---")


with c0:
    col1, col2, col3 = st.columns([1, 1, 1])
    data_options = {"int": "整數", "char": "字元"}
    data = col1.selectbox(
        "data",
        options=data_options,
        format_func=lambda x: f"{data_options.get(x)} {x}",
        index=0,
    )

    mode_options = {"recursion": "遞迴", "iteration": "迭代"}
    mode = col2.selectbox(
        "mode",
        options=mode_options,
        format_func=lambda x: f"{mode_options.get(x)} {x}",
        index=1,
    )

    if data == "char":
        input_case_options = {
            "lower": "小寫",
            "upper": "大寫",
            "both": "小寫+大寫",
        }
        input_case = col3.selectbox(
            label="case",
            options=input_case_options,
            format_func=lambda x: input_case_options.get(x),
            index=0,
        )


def validate_vector(vector_str: str):
    input_vector = vector_str.split(",")
    l = list()
    for i, input_data in enumerate(input_vector):
        try:
            input_data = input_data.strip()
            if data == "char":
                if len(input_data) == 0:
                    raise ValueError(
                        f"尾端如果沒有{data_options.get(data)}不需要添加逗號"
                    )
                if len(input_data) != 1:
                    raise ValueError(f"{input_data} 不是正確的{data_options.get(data)}")
                if input_data.isdigit():
                    raise ValueError(f"{input_data} 不是正確的{data_options.get(data)}")
            elif data == "int":
                if not input_data.isdigit():
                    raise ValueError(f"{input_data} 不是正確的{data_options.get(data)}")
                input_data = int(input_data)

            if input_data in l:
                raise ValueError(f"{input_data} 重複，在索引為 {i} 的位置")
            else:
                l.append(input_data)

        except ValueError as e:
            st.error(e)
            return None
    return l


if "toggled" not in st.session_state:
    st.session_state.toggled = False


with c1:
    col1, col2 = st.columns([1, 1])
    with col1:
        input_options_action = {
            "create": "新增",
            "search": "搜尋",
            "delete": "刪除",
            "construct_tree": "建構樹",
        }

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
            if data == "int":
                input_data = st.number_input("int", min_value=0, max_value=2**31 - 1)
            else:
                input_data = st.text_input("char", max_chars=1)
            sidebar_text_list.append(
                f"`{data}`：輸入二元樹的{data_options.get(data)}。"
            )

        else:
            col1, col2 = st.columns([1, 3], gap="medium")
            sidebar_text_list.append(
                f"`n`：隨機輸入二元樹 n 個{data_options.get(data)}。"
            )
            with col1:
                input_n = st.number_input("n", min_value=1, max_value=100, value=3)
            with col2:
                if data == "int":
                    input_minmax = st.slider(
                        "minmax",
                        min_value=0,
                        max_value=1000,
                        value=(0, 100),
                    )

                    sidebar_text_list.append(
                        f"`mixmax`：輸入{data_options.get(data)}的最大最小值。"
                    )
                else:
                    pass
    elif input_action in ["search", "delete"]:
        if data == "int":
            input_target = st.number_input("target", min_value=0, max_value=2**31 - 1)
        elif data == "char":
            input_target = st.text_input("target", max_chars=1)

        sidebar_text_list.append(
            f"`target`：欲{input_options_action.get(input_action)}的{data_options.get(data)}"
        )

    else:
        col1, col2 = st.columns([2, 1])
        construct_tree_option = {
            "prefixinfix": "前序 + 中序",
            "postfixinfix": "後序 + 中序",
        }
        construct_tree_input = col1.radio(
            label="construct tree",
            options=construct_tree_option,
            format_func=lambda x: construct_tree_option.get(x),
        )
        example_btn = col2.button(
            f"讀取{construct_tree_option.get(construct_tree_input)}的範例"
        )
        if example_btn:
            if data == "char":
                st.session_state.infix = "H, B, J, A, F, D, G, C, E"
                st.session_state.prefix = "A, B, H, J, C, D, F, G, E"
                st.session_state.postfix = "H, J, B, A, F, D, G, C, E"
            else:
                st.session_state.infix = "8, 2, 9, 1, 6, 4, 7, 3, 5"
                st.session_state.prefix = "1, 2, 8, 9, 3, 4, 6, 7, 5"
                st.session_state.postfix = "8, 9, 2, 1, 6, 4, 7, 3, 5"
        infix_vector_input = st.text_input("infix", help="以逗點做分隔", key="infix")
        if infix_vector_input != "":
            validate_result = validate_vector(infix_vector_input)
        if construct_tree_input == "prefixinfix":
            prefix_vector_input = st.text_input(
                "prefix", help="以逗點做分隔", key="prefix"
            )
            if prefix_vector_input != "":
                validate_result = validate_vector(prefix_vector_input)
        elif construct_tree_input == "postfixinfix":
            postfix_vector_input = st.text_input(
                "post", help="以逗點做分隔", key="postfix"
            )
            if postfix_vector_input != "":
                validate_result = validate_vector(postfix_vector_input)

        sidebar_text_list.append(
            f"`foofix`：輸入以逗點做為分隔的{data_options.get(data)}陣列"
        )

    col1, col2, _, _ = st.columns([2, 2, 2, 7])
    btn_action = col1.button(
        input_options_action.get(input_action),
        type="primary",
        use_container_width=True,
    )

    btn_empty = col2.button(
        ":violet[清空 :bomb:]", type="secondary", use_container_width=True
    )


@st.cache_resource
def init_bst():
    return BinarySearchTreeInt()


@st.cache_resource
def init_bst_char():
    return BinarySearchTreeChar()


bst = init_bst()
bst_char = init_bst_char()


def get_input_data_list():
    if input_case == "lower":
        s = string.ascii_lowercase
    elif input_case == "upper":
        s = string.ascii_uppercase
    else:
        s = string.ascii_letters
    return list(s)


def get_current_tree():
    if data == "int":
        return bst
    else:
        return bst_char


def insert(input_data: int | str):
    if mode == "recursion":
        get_current_tree().insert(input_data)
    else:
        get_current_tree().insert_iter(input_data)

    st.toast(f"已新增 {input_data} 到二元樹中 ({mode_options.get(mode)})")


def search(target: int):
    if mode == "recursion":
        result = get_current_tree().search(target)
    else:
        result = get_current_tree().search_iter(target)

    if result:
        st.info(f"{target} 找到ㄌ ({mode_options.get(mode)})")
    else:
        st.error(f"找不到 {target}! ({mode_options.get(mode)})")
        col1, col2, _ = st.columns([2, 2, 10])
        col1.button(
            f"新增 {target}",
            on_click=insert,
            kwargs={"input_data": target},
            type="primary",
            use_container_width=True,
        )
        col2.button("忽略", use_container_width=True)


def delete(target: int):
    if mode == "recursion":
        result = get_current_tree().search(target)
        if result:
            get_current_tree().delete(target)
            st.info(
                f"刪除了{data_options.get(data)} {target} ({mode_options.get(mode)})"
            )
        else:
            st.error(f"找不到 {target}! ({mode_options.get(mode)})")
            col1, col2, _ = st.columns([2, 2, 10])
            col1.button(
                f"新增 {target}",
                on_click=insert,
                kwargs={"input_data": target},
                type="primary",
                use_container_width=True,
            )
            col2.button("忽略", use_container_width=True)
    else:
        result = get_current_tree().delete_iter(target)
        if result == -1:
            st.error(f"找不到 {target}! ({mode_options.get(mode)})")
            col1, col2, _ = st.columns([2, 2, 10])
            col1.button(
                f"新增 {target}",
                on_click=insert,
                kwargs={"input_data": target},
                type="primary",
                use_container_width=True,
            )
            col2.button("忽略", use_container_width=True)
        else:
            st.info(
                f"刪除了{data_options.get(data)} {target} ({mode_options.get(mode)})"
            )


def empty():
    get_current_tree().empty()


if btn_action:
    st.session_state.toggled = True
    if input_action == "create":
        if input_method == "manual":
            if isinstance(input_data, int):
                insert(input_data)
            elif isinstance(input_data, str):
                result = re.match(r"[a-zA-Z]{1}", input_data)
                if result is None:
                    st.error("請輸入正確的英文字母")
                else:
                    insert(input_data)
        else:
            if data == "int":
                m, M = input_minmax
                for _ in range(input_n):
                    num = random.randint(m, M)
                    insert(num)
            else:
                input_data_list = get_input_data_list()
                if input_n > len(input_data_list):
                    st.error(
                        f"輸入數字應小於{input_case_options.get(input_case)}的總字元數 {len(input_data_list)}"
                    )
                else:
                    nums = random.sample(population=input_data_list, k=input_n)
                    for num in nums:
                        insert(num)

    elif input_action == "search":
        search(input_target)
    elif input_action == "delete":
        delete(input_target)
    elif input_action == "construct_tree":
        empty()

        infix_vector = validate_vector(infix_vector_input)
        if construct_tree_input == "prefixinfix":
            prefix_vector = validate_vector(prefix_vector_input)
            if infix_vector is not None and prefix_vector is not None:
                get_current_tree().construct_infix_prefix(infix_vector, prefix_vector)

        elif construct_tree_input == "postfixinfix":
            postfix_vector = validate_vector(postfix_vector_input)
            if infix_vector is not None and postfix_vector is not None:
                get_current_tree().construct_infix_postfix(infix_vector, postfix_vector)

if btn_empty:
    empty()


code = st.code(language="css", body="", line_numbers=True)

st.sidebar.markdown("\n\n".join(sidebar_text_list))
if st.session_state.toggled:
    with rd.stdout(to=code):
        if output_action == "preorder":
            get_current_tree().print(0, mode == "iteration")
        elif output_action == "inorder":
            get_current_tree().print(1, mode == "iteration")
        elif output_action == "postorder":
            get_current_tree().print(2, mode == "iteration")
        else:
            get_current_tree().print(3, mode == "iteration")
